
import os;
import os.path;

pj = os.path.join;

# If we have pysvn, load it
try:
    import pysvn
    have_pysvn = True
except:
    have_pysvn = False


class RevisionTagWriter(object):
    """
    For each library the corresponding <Libname>Def.cpp file is located and
    the highest revision number of any of the lib's source files is recorded
    together with a marker if the lib contains local changes.
    """
    def __init__(self, libMap):
        """
        Create a new tag writer that uses the libraries from the given libMap.
        Also checks if pysvn is available - without it tagging is not possible.
        """
        if not have_pysvn:
            raise "The module pysvn is required to perform revision tagging!"
        
        self.libMap        = libMap
        self.maxRev        = 0
        self.svnClient     = pysvn.Client()
        self.versionString = open("VERSION").readline().strip()
    
    def run(self):
        """
        Write revision tags.
        """
        for (libName, libObj) in self.libMap.iteritems():
            libMaxRev   = 0
            modifiedStr = ""
            
            for file in libObj.source_files + libObj.header_files:
                filename = pj("Source", file)
                
                fileRev, fileModified = self._getSVNInfo(filename)
                
                if libMaxRev < fileRev:
                    libMaxRev = fileRev
                
                # we modify the <libname>Def.cpp files ourselves
                if fileModified and filename[-7:] != "Def.cpp":
                    print "%s: file %s is modified!" % (libName, filename)
                    modifiedStr = " !MODIFIED!"
            
            if modifiedStr != "":
                print "%s: There are modified files, revision might be inaccurate!" % libName
            print "%s: Highest revision: %d." % (libName, libMaxRev)
            
            if self.maxRev < libMaxRev:
                self.maxRev = libMaxRev
            
            for file in libObj.source_files:
                if file[-7:] == "Def.cpp":
                    filename = pj("Source", file)
                    fileInfo = self.svnClient.info(filename)
                    repoPath = fileInfo.url[len(fileInfo.repos):-len(filename)-1]
                    
                    fileContents = open(filename).readlines()
                    for i in range(len(fileContents)):
                        if fileContents[i][:22] == '#define SVN_REVISION "':
                            fileContents[i] = '#define SVN_REVISION "%d  (%s)%s"\n' % (libMaxRev, repoPath, modifiedStr)
                            break
                    open(filename, "w").writelines(fileContents)
        
        # Update the documentation mainfile
        # Find the high version for stuff in Doc/, too
        modifiedStr = ""
        for file in glob.glob("Doc/*"):
            print file
            fileRev, fileMod = self._getSVNInfo(file)
            
            if self.maxRev < fileRev:
                self.maxRev = fileRev
            if fileMod:
                modifiedStr = " !Modified!"
        
        filename     = "Doc/mainpage.dox"
        fileContents = open(filename).readlines()
        for i in range(len(fileContents)):
            if fileContents[i][:7] == 'version':
                fileContents[i] = 'version %s r%d %s\n' % (self.versionString, self.maxRev, modifiedStr)
                break
        open(filename,'w').writelines(fileContents)

    def _getSVNInfo(self, filename):
        """
           Get the svn info for the given file.
           Returns a version, modified tuple.
        """
        fileInfo   = self.svnClient.info  (filename)
        fileStatus = self.svnClient.status(filename)
        
        fileRev = 0
        fileMod = False
        
        # Ignore unversioned files
        if pysvn.wc_status_kind.unversioned != fileStatus[0].text_status and \
           pysvn.wc_status_kind.ignored     != fileStatus[0].text_status:
            fileRev = fileInfo.revision.number
            fileMod = pysvn.wc_status_kind.modified == fileStatus[0].text_status

        return fileRev, fileMod
