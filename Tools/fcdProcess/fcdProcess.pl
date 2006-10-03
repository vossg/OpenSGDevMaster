#!/usr/bin/perl -w

use strict;

my $gfc;
my $gfcdXml = '';
my $currElem;

my $filePrefix    = "OSG";
my $decFileSuffix = ".h";
my $inlFileSuffix = ".inl";
my $impFileSuffix = ".cpp";

my $baseTmplCpp = "FCBaseTemplate_cpp.h";
my $baseTmplH   = "FCBaseTemplate_h.h";
my $baseTmplInl = "FCBaseTemplate_inl.h";

my $fieldImpH  = "FCFieldsTemplate_h.h";

my $fcTmplCpp   = "FCTemplate_cpp.h";
my $fcTmplH     = "FCTemplate_h.h";
my $fcTmplInl   = "FCTemplate_inl.h";

my $enableCompat = 0;

sub start_element 
{
  my ($self,$localname) = @_;

  if($localname eq "FieldContainer")
  {
#      print "Create FieldContainer $self\n";

      $gfc = new OSGFieldContainer;

      while(@_)
      {
          my $key = shift;
          my $val = shift;

          $gfc->{$key} = $val;
      }

      my @fArray = ();
      my $fArrayRef = \@fArray;

      $gfc->{fields} = $fArrayRef;

      $currElem = $gfc;
  }

  if($localname eq "Field")
  {
#      printf "Create Field\n";

      my $field = new OSGField;

      while(@_)
      {
          my $key = shift;
          my $val = shift;

          $field->{$key} = $val;
      }
      
      my $fArrayRef = $gfc->{fields};

      push @$fArrayRef, $field;

      $currElem = $field;
  }
}

sub end_element 
{
}

sub characters 
{
    my $self = shift;

    my $a1 = shift;

    if($a1 ne "\n" && $a1 ne "\t")
    {
        $currElem->{description} .= "$a1\n";
#        print "Foo -$a1-\n";
    }
}

package OSGFieldContainer;
use strict;

sub new
{
    my $class = shift;
    my $self  = {};

    $self->{name}                  = "<UNDEF>";
    $self->{parent}                = "<UNDEF>";
    $self->{library}               = "<UNDEF>";
    $self->{pointerfieldtypes}     = "none";
    $self->{structure}             = "<UNDEF>";
    $self->{systemcomponent}       = "true";
    $self->{parentsystemcomponent} = "true";
    $self->{decoratable}           = "false";
    $self->{useLocalIncludes}      = "false";
    $self->{isNodeCore}            = "false";
    $self->{description}           = "";
    $self->{group}                 = "NULL";
    $self->{namespace}             = 0;
    $self->{decorateeFieldFlags}   = "";
    $self->{CompatOneSix}          = "false";

    bless $self, $class
}

sub isSystemComponent
{
    my $self = shift;

    return $self->{systemcomponent};
}

sub isDecoratable
{
    my $self = shift;

    return $self->{isDecoratable};
}

sub hasFields
{
    my $self = shift;

    return $self->{hasFields};
}

sub addFieldIdsAndMasksDecl
{
    my $self    = shift;
    my $destRef = shift;
    my $tmpLine;

    my $fArrayRef   = $self->{fields};
    my @aArrayField = @{$self->{fields}};

    if($self->{hasFields} eq "false")
    {
        return;
    }

    push(@$destRef, "    enum\n");
    push(@$destRef, "    {\n");

    $tmpLine  = "        ";
    $tmpLine .= $aArrayField[0]->{Fieldname};
    $tmpLine .= "FieldId = Inherited::NextFieldId,\n";

    push(@$destRef, $tmpLine);
    

    for(my $i = 1; $i <= $#aArrayField; $i++)
    {
        $tmpLine  = "        ";
        $tmpLine .= $aArrayField[$i]->{Fieldname};
        $tmpLine .= "FieldId = ";
        $tmpLine .= $aArrayField[$i - 1]->{Fieldname};
        $tmpLine .= "FieldId + 1,\n";

        push(@$destRef, $tmpLine);
    }
        

    $tmpLine  = "        ";
    $tmpLine .= "NextFieldId = ";
    $tmpLine .= $aArrayField[$#aArrayField]->{Fieldname};
    $tmpLine .= "FieldId + 1\n";

    push(@$destRef, $tmpLine);

    push(@$destRef, "    };\n\n");

    for(my $i = 0; $i <= $#aArrayField; $i++)
    {
        $tmpLine  = "    static const OSG::BitVector ";
        $tmpLine .= $aArrayField[$i]->{Fieldname};
        $tmpLine .= "FieldMask = \n";

        push(@$destRef, $tmpLine);

        $tmpLine   = "        (TypeTraits<BitVector>::One << ";
        $tmpLine  .= $aArrayField[$i]->{Fieldname};
        $tmpLine  .= "FieldId);\n";

        push(@$destRef, $tmpLine);
    }

    $tmpLine  = "    static const OSG::BitVector NextFieldMask = \n";

    push(@$destRef, $tmpLine);

    $tmpLine   = "        (TypeTraits<BitVector>::One << NextFieldId);\n";
    
    push(@$destRef, $tmpLine);

}

sub addAdditionaIncludes
{
    my $self    = shift;
    my $destRef = shift;
    my $tmpLine;

    if(exists $self->{'additionalIncludes'})
    {
        my @addIncludes = split(/,/,$self->{'additionalIncludes'});
        
        
        for my $addInclude (@addIncludes)
        {
            push(@$destRef, "#include <$addInclude>");
        }
    }
}

sub setupDecorator
{
    my $self = shift;

    $self->{Classname} = $self->{name}."Decorator";
    $self->{CLASSNAME} = uc($self->{name})."DECORATOR";
    $self->{Parent}    = $self->{name};
}

sub setupFieldContainer
{
    my $self = shift;

    $self->{Classname} = $self->{name};
    $self->{CLASSNAME} = uc($self->{name});
    $self->{Parent}    = $self->{parent};
}

sub finalize
{
    my $self = shift;

    my $fArrayRef   = $self->{fields};
    my @aArrayField = @{$self->{fields}};

#    print "Finalize $fArrayRef $#$fArrayRef \n";

    if($#$fArrayRef != -1)
    {
        ${self}->{hasFields} = "true";
    }
    else
    {
        ${self}->{hasFields} = "false";
    }

    if(exists ${self}->{library})
    {
        ${self}->{Library} = "true";
        ${self}->{Libname} =    ${self}->{library};
        ${self}->{LIBNAME} = uc(${self}->{library});
    }
    else
    {
        ${self}->{Library} = "false";
        ${self}->{Libname} = "<UNDEF>";
        ${self}->{LIBNAME} = "<UNDEF>";
    }

    $self->{CLASSNAME}     = uc($self->{name});
    $self->{Classname}     = $self->{name};
    $self->{isDecoratable} = $self->{decoratable};
    $self->{Parent}        = $self->{parent};

    if($self->{structure} eq "concrete")
    {
        $self->{Abstract} = "false";
    }
    else
    {
        $self->{Abstract} = "true";
    }

    if($self->{parentsystemcomponent} eq "true" &&
       $self->{systemcomponent}       eq "false" )
    {
        $self->{ParentHeaderPrefix} = "OpenSG/";
    }
    else
    {
        $self->{ParentHeaderPrefix} = "";
    }

    if($self->{systemcomponent} eq "false")
    {
        $self->{HeaderPrefix} = "OpenSG/";
    }
    else
    {
        $self->{HeaderPrefix} = "";
    }

    $self->{hasPrivateFields}   = "false";
    $self->{hasProtectedFields} = "false";
    $self->{hasPublicFields}    = "false";
    $self->{hasPtrFields}       = "false";

    my @sfArray = ();
    my @mfArray = ();

#    $self->{fields} = $fArrayRef;

    for my $field (@$fArrayRef)
    {
        $field->finalize($self);

        if($field->isPrivate() eq "true")
        {
            $self->{hasPrivateFields} = "true";            
        }

        if($field->isProtected() eq "true")
        {
            $self->{hasProtectedFields} = "true";            
        }

        if($field->isPublic() eq "true")
        {
            $self->{hasPublicFields} = "true";            
        }

        if($field->isSField() eq "true")
        {
            push(@sfArray, $field);
        }

        if($field->isMField() eq "true")
        {
            push(@mfArray, $field);
        }

        if($field->isPtrField() eq "true")
        {
            $self->{hasPtrFields} = "true";
        }
    }

    if($#$fArrayRef != -1)
    {
        $$fArrayRef[$#$fArrayRef]->{FieldSeparator} = "";
    }

    my $sfArrayRef = \@sfArray;
    my $mfArrayRef = \@mfArray;

    $self->{SFields} = $sfArrayRef;
    $self->{MFields} = $mfArrayRef;

    $self->{abstract} = "false";

    if($self->{structure} eq "concrete")
    {
        $self->{abstract} = "false";
    }

    if($self->{structure} eq "abstract")
    {
        $self->{abstract} = "true";
    }

    $self->{Pointerfield}   = "false";
    $self->{SFPointerfield} = "false";
    $self->{MFPointerfield} = "false";

    if($self->{pointerfieldtypes} eq "both")
    {
        $self->{Pointerfield}   = "true";
        $self->{SFPointerfield} = "true";
        $self->{MFPointerfield} = "true";
    }

    if($self->{pointerfieldtypes} eq "single")
    {
        $self->{Pointerfield}   = "true";
        $self->{SFPointerfield} = "true";
    }

    if($self->{pointerfieldtypes} eq "multi")
    {
        $self->{Pointerfield}   = "true";
        $self->{MFPointerfield} = "true";
    }

    $self->{Description} = $self->{description};
    my $safe_desc = $self->{description};
    $safe_desc =~ s/"/\\\\\\"/g;
    $safe_desc =~ s/\n/\\\\n/g;
    $self->{SafeDescription} = $safe_desc;

    $self->{SystemComponent} = $self->{systemcomponent};

    $self->{FieldMethodType} = "";

    if($self->isDecoratable() eq "true")
    {
        $self->{FieldMethodType} = "virtual";
    }

    $self->{Group}     = $self->{group};
    $self->{Namespace} = $self->{namespace};

    if($self->{decorateeFieldFlags} eq "")
    {
        $self->{decorateeFieldFlags} = "Field::SFDefaultFlags";
    }
    else
    {
        my @flags = split(/[,]/, $self->{decorateeFieldFlags});

        $self->{decorateeFieldFlags} = "(";

        for(my $i = 0; $i <= $#flags; ++$i)
        {
            my $flag = $flags[$i];

            $flag =~ s/ //g;
            $flag =~ s/\t//g;
            $flag =~ s/\n//g;

            if($i == 0 && $i != $#flags)
            {
                $self->{decorateeFieldFlags} .= "Field::".$flag." |";
                
                next;
            }

            if($i == $#flags)
            {
                if($i == 0)
                {
                    $self->{decorateeFieldFlags} .= "Field::".$flag;
                }
                else
                {
                    $self->{decorateeFieldFlags} .= " Field::".$flag;
                }

                next;
            }

            $self->{decorateeFieldFlags} .= " Field::".$flag." |";
        }
    
        $self->{fdecorateeFieldFlags} .= ")";
    }

    if($enableCompat == 1)
    {
        $self->{CompatOneSix} = "true";
    }
    else
    {
        $self->{CompatOneSix} = "false";
    }
}

sub dumpValues
{
    my $self = shift;

    print "FieldContainer\n";
    print "\tname                   : $self->{name}\n";
    print "\tparent                 : $self->{parent}\n";
    print "\tlibrary                : $self->{library}\n";
    print "\tpointerfieldtypes      : $self->{pointerfieldtypes}\n";
    print "\tstructure              : $self->{structure}\n";
    print "\tsystemcomponent        : $self->{systemcomponent}\n";
    print "\tparentsystemcomponent  : $self->{parentsystemcomponent}\n";
    print "\tdecoratable            : $self->{decoratable}\n";
    print "\tuseLocalIncludes       : $self->{useLocalIncludes}\n";
    print "\tgroup                  : $self->{group}\n";
    print "\tnamespace              : $self->{namespace}\n";
    
    print "\tDerived                : \n";
    print "\t  hasFields              : $self->{hasFields}\n";
    print "\t  Library                : $self->{Library}\n";
    print "\t  CLASSNAME              : $self->{CLASSNAME}\n";
    print "\t  Classname              : $self->{Classname}\n";
    print "\t  Parent                 : $self->{Parent}\n";
    print "\t  Libname                : $self->{Libname}\n";
    print "\t  LIBNAME                : $self->{LIBNAME}\n";
    print "\t  isDecoratable          : $self->{isDecoratable}\n";
    print "\t  Abstract               : $self->{Abstract}\n";
    print "\t  HeaderPrefix           : $self->{HeaderPrefix}\n";
    print "\t  ParentHeaderPrefix     : $self->{ParentHeaderPrefix}\n";
    print "\t  hasPrivateFields       : $self->{hasPrivateFields}\n";
    print "\t  hasProtectedFields     : $self->{hasProtectedFields}\n";
    print "\t  hasPublicFields        : $self->{hasPublicFields}\n";
    print "\t  hasPtrFields           : $self->{hasPtrFields}\n";
    print "\t  Pointerfield           : $self->{Pointerfield}\n";
    print "\t  SFPointerfield         : $self->{SFPointerfield}\n";
    print "\t  MFPointerfield         : $self->{MFPointerfield}\n";
    print "\t  Description            : $self->{Description}\n";
    print "\t  SystemComponent        : $self->{SystemComponent}\n";
    print "\t  FieldMethodType        : $self->{FieldMethodType}\n";
    print "\t  Group                  : $self->{Group}\n";
    print "\t  Namespace              : $self->{Namespace}\n";

    my $fArrayRef = $self->{fields};

    for my $field (@$fArrayRef)
    {
        $field->dumpValues();
    }

}


package OSGField;
use strict;

%OSGField::isPerFieldIf = ();

$OSGField::isPerFieldIf{'FieldNamespace'}              = "true";
$OSGField::isPerFieldIf{'isPrivate'}                   = "true";
$OSGField::isPerFieldIf{'isProtected'}                 = "true";
$OSGField::isPerFieldIf{'isPublic'}                    = "true";
$OSGField::isPerFieldIf{'hasDefaultHeader'}            = "true";
$OSGField::isPerFieldIf{'isMField'}                    = "true";
$OSGField::isPerFieldIf{'isSField'}                    = "true";
$OSGField::isPerFieldIf{'isPtrField'}                  = "true";
$OSGField::isPerFieldIf{'checkNilPtr'}                 = "true";
$OSGField::isPerFieldIf{'linkSParent'}                 = "true";
$OSGField::isPerFieldIf{'linkMParent'}                 = "true";
$OSGField::isPerFieldIf{'doRefCount'}                  = "true";
$OSGField::isPerFieldIf{'passFieldMask'}               = "true";
$OSGField::isPerFieldIf{'removeToSet'}                 = "true";
$OSGField::isPerFieldIf{'clearMField'}                 = "true";
$OSGField::isPerFieldIf{'writePushToField'}            = "true";
$OSGField::isPerFieldIf{'writeInsertIntoMField'}       = "true";
$OSGField::isPerFieldIf{'writeReplaceInMFieldIndex'}   = "true";
$OSGField::isPerFieldIf{'writeReplaceInMFieldObject'}  = "true";
$OSGField::isPerFieldIf{'writeRemoveFromMFieldIndex'}  = "true";
$OSGField::isPerFieldIf{'writeRemoveFromMFieldObject'} = "true";
$OSGField::isPerFieldIf{'writeClearField'}             = "true";
$OSGField::isPerFieldIf{'needClassInclude'}            = "true";

sub new
{
    my $class = shift;
    my $self  = {};

    $self->{name}                     = "<UNDEF>";
    $self->{type}                     = "<UNDEF>";
    $self->{cardinality}              = "<UNDEF>";
    $self->{FieldNamespace}           = "";
    $self->{visibility}               = "external";
    $self->{fieldFlags}               = "";
#mtinf
    $self->{defaultValue}             = "";
    $self->{access}	                  = "public";
    $self->{defaultHeader}            = "";
    $self->{header}                   = "auto";
    $self->{description}              = "";

    $self->{checkNilPtr}              = "true";
    $self->{linkSParent}              = "false";
    $self->{linkMParent}              = "false";
    $self->{doRefCount}               = "true";
    $self->{passFieldMask}            = "false";

    $self->{removeTo}                 = "";
    $self->{removeToSet}              = "false";   
    $self->{clearMField}              = "true";

    $self->{pushToField}              = "";
    $self->{insertIntoMField}         = "";
    $self->{replaceInMFieldIndex}     = "";
    $self->{replaceInMFieldObject}    = "";
    $self->{removeFromMFieldIndex}    = "";
    $self->{removeFromMFieldObject}   = "";
    $self->{clearField}               = "";

    $self->{pushToFieldAs}            = "";
    $self->{insertIntoMFieldAs}       = "";
    $self->{replaceInMFieldIndexAs}   = "";
    $self->{replaceInMFieldObjectAs}  = "";
    $self->{removeFromMFieldIndexAs}  = "";
    $self->{removeFromMFieldObjectAs} = "";
    $self->{clearFieldAs}             = "";

    $self->{needClassInclude}         = "true";

    bless $self, $class
}

sub isPrivate
{
    my $self = shift;

    return $self->{isPrivate};
}

sub isProtected
{
    my $self = shift;

    return $self->{isProtected};
}

sub isPublic
{
    my $self = shift;

    return $self->{isPublic};
}

sub isSField
{
    my $self = shift;

    return $self->{isSField};
}

sub isMField
{
    my $self = shift;

    return $self->{isMField};
}

sub isPtrField
{
    my $self = shift;

    return $self->{isPtrField};
}

sub dumpValues
{
    my $self = shift;

    print "\n\tField\n";
    print "\t\tname                     : $self->{name}\n";
    print "\t\ttype                     : $self->{type}\n";
    print "\t\tcardinality              : $self->{cardinality}\n";
    print "\t\tvisibility               : $self->{visibility}\n";
    print "\t\tdefaultValue             : $self->{defaultValue}\n";
    print "\t\taccess                   : $self->{access}\n";
    print "\t\tdefaultHeader            : $self->{defaultHeader}\n";
    print "\t\theader                   : $self->{header}\n";
    print "\t\tcheckNilPtr              : $self->{checkNilPtr}\n";
    print "\t\tlinkSParent              : $self->{linkSParent}\n";
    print "\t\tlinkMParent              : $self->{linkMParent}\n";
    print "\t\tdoRefCount               : $self->{doRefCount}\n";
    print "\t\tpassFieldMask            : $self->{passFieldMask}\n";
    print "\t\tremoveTo                 : $self->{removeTo}\n";
    print "\t\tremoveToSet              : $self->{removeToSet}\n";
    print "\t\tclearMField              : $self->{clearMField}\n";
    print "\t\tpushToField              : $self->{pushToField}\n";
    print "\t\tinsertIntoMField         : $self->{insertIntoMField}\n";
    print "\t\treplaceInMFieldIndex     : $self->{replaceInMFieldIndex}\n";
    print "\t\treplaceInMFieldObject    : $self->{replaceInMFieldObject}\n";
    print "\t\tremoveFromMFieldIndex    : $self->{removeFromMFieldIndex}\n";
    print "\t\tremoveFromMFieldObject   : $self->{removeFromMFieldObject}\n";
    print "\t\tclearField               : $self->{clearField}\n";
    print "\t\tpushToFieldAs            : $self->{pushToFieldAs}\n";
    print "\t\tinsertIntoMFieldAs       : $self->{insertIntoMFieldAs}\n";
    print "\t\treplaceInMFieldIndexAs   : $self->{replaceInMFieldIndexAs}\n";
    print "\t\treplaceInMFieldObjectAs  : $self->{replaceInMFieldObjectAs}\n";
    print "\t\tremoveFromMFieldIndexAs  : $self->{removeFromMFieldIndexAs}\n";
    print "\t\tremoveFromMFieldObjectAs : $self->{removeFromMFieldObjectAs}\n";
    print "\t\tclearFieldAs             : $self->{clearFieldAs}\n";

    print "\n\t\tDerived :\n";
    print "\t\t\tFieldname                   : $self->{Fieldname}\n";
    print "\t\t\tFieldtype                   : $self->{Fieldtype}\n";
    print "\t\t\tFieldtypeCapsClean          : $self->{FieldtypeCapsClean}\n";
    print "\t\t\tCapsFieldtypeClean          : $self->{CapsFieldtypeClean}\n";
    print "\t\t\tisPrivate                   : $self->{isPrivate}\n";
    print "\t\t\tisProtected                 : $self->{isProtected}\n";
    print "\t\t\tisPublic                    : $self->{isPublic}\n";
    print "\t\t\tCARDINALITY                 : $self->{CARDINALITY}\n";
    print "\t\t\tFieldMethodType             : $self->{FieldMethodType}\n";
    print "\t\t\tfieldname                   : $self->{fieldname}\n";
    print "\t\t\tFieldSeparator              : $self->{FieldSeparator}\n";
    print "\t\t\thasDefaultHeader            : $self->{hasDefaultHeader}\n";
    print "\t\t\tfieldnameDesc               : $self->{fieldnameDesc}\n";
    print "\t\t\tfieldvisibility             : $self->{fieldvisibility}\n";
    print "\t\t\tFielddescription            : $self->{Fielddescription}\n";
    print "\t\t\tisSField                    : $self->{isSField}\n";
    print "\t\t\tisMField                    : $self->{isMField}\n";
    print "\t\t\tisPtrField                  : $self->{isPtrField}\n";
    print "\t\t\tpushToField                 : $self->{pushToField}\n";
    print "\t\t\twriteInsertIntoMField       : $self->{insertIntoMField}\n";
    print "\t\t\twriteReplaceInMFieldIndex   : $self->{replaceInMFieldIndex}\n";
    print "\t\t\twritePeplaceInMFieldObject  : $self->{replaceInMFieldObject}\n";
    print "\t\t\twriteRemoveFromMFieldIndex  : $self->{removeFromMFieldIndex}\n";
    print "\t\t\twriteRemoveFromMFieldObject : $self->{removeFromMFieldObject}\n";
    print "\t\t\twriteClearField             : $self->{clearField}\n";
}

sub finalize
{
    my $self = shift;
    my $fc   = shift;

    my $cleanType;

    $cleanType = $self->{type};
    
    $cleanType =~ s/^std:://;
    
    $self->{Fieldname}          = ucfirst($self->{name});
    $self->{Fieldtype}          = $self->{type};
    $self->{FieldtypeCapsClean} = ucfirst($cleanType);
    $self->{CapsFieldtypeClean} = ucfirst($cleanType);

    $self->{isPrivate}   = "false";
    $self->{isProtected} = "false";
    $self->{isPublic}    = "false";

    if($self->{access} eq "private")
    {
        $self->{isPrivate} = "true";
    }
    elsif($self->{access} eq "protected")
    {
        $self->{isProtected} = "true";
    }
    elsif($self->{access} eq "public")
    {
        $self->{isPublic} = "true";
    }

    $self->{isMField} = "false";
    $self->{isSField} = "false";

    if($self->{cardinality} eq "single")
    {
        $self->{isSField} = "true";
    }

    if($self->{cardinality} eq "multi")
    {
        $self->{isMField} = "true";
    }

    if($self->{header} eq "" || $self->{header} eq "auto")
    {
        if($fc->isSystemComponent() eq "true")
        {
            $self->{FieldtypeInclude} = "OSG"
        }
        else
        {
            $self->{FieldtypeInclude} = "OpenSG/OSG"
        }

        $self->{FieldtypeInclude} .= $self->{FieldtypeCapsClean};
        $self->{FieldtypeInclude} =~ s/Ptr$//;
        $self->{FieldtypeInclude} =~ s/GLP:://;
        $self->{FieldtypeInclude} .= "Fields.h";
    }
    else
    {
        $self->{FieldtypeInclude}   = $self->{header};
    }

    $self->{fieldname}   = "";

    if($self->isSField() eq "true")
    {
        $self->{CARDINALITY} = "SF";
        $self->{fieldname}   = "sf";
    }

    if($self->isMField() eq "true")
    {
        $self->{CARDINALITY} = "MF";
        $self->{fieldname}   = "mf";
    }

    if($self->{CapsFieldtypeClean} =~ m/([A-Za-z_]*)::/)
    {
        $self->{FieldNamespace} = "$1::";
        $self->{CapsFieldtypeClean} =~ s/$1:://;
    }

    $self->{fieldname} .= $self->{Fieldname};

    $self->{FieldMethodType} = "";

    if($fc->isDecoratable() eq "true")
    {
        $self->{FieldMethodType} = "virtual";
    }

    $self->{FieldSeparator} = ",";

    if(exists $self->{defaultHeader} && $self->{defaultHeader} ne "")
    {
        $self->{hasDefaultHeader} = "true";

        if(! ($self->{defaultHeader} =~ m/\"|</))  #"
        {
            $self->{defaultHeader} = '"'.$self->{defaultHeader}.'"';
        }        
    }
    else
    {
        $self->{hasDefaultHeader} = "false";
    }

    if(exists $self->{defaultValue} && $self->{defaultValue} ne "")
    {
        $self->{FieldTypedDefault}  = $self->{type};

        $self->{FieldTypedDefault} .= "(";

        if($self->{type} =~ m/std::string/)
        {
            $self->{FieldTypedDefault} .= "\"";
        }

        $self->{FieldTypedDefault} .= $self->{defaultValue};

        if($self->{type} =~ m/std::string/)
        {
            $self->{FieldTypedDefault} .= "\"";
        }

        $self->{FieldTypedDefault} .= ")";
    }
    else
    {
        $self->{FieldTypedDefault} = "";
    }

    $self->{fieldnameDesc}   = $self->{name};

    if($self->{visibility} eq "external")
    {
        $self->{fieldvisibility} = "false";
    }

    if($self->{visibility} eq "internal")
    {
        $self->{fieldvisibility} = "true";
    }

    my $fieldFlagsOverride = 0;
    
    if($self->{isSField} eq "true")
    {
        if($self->{fieldFlags} eq "")
        {
            $self->{fieldFlags} = "Field::SFDefaultFlags";
        }
        else
        {
            $fieldFlagsOverride = 1;
        }
    }
    else
    {
        if($self->{fieldFlags} eq "")
        {
            $self->{fieldFlags} = "Field::MFDefaultFlags";
        }
        else
        {
            $fieldFlagsOverride = 1;
        }
    }

    if($fieldFlagsOverride == 1)
    {
        my @flags = split(/[,]/, $self->{fieldFlags});

        $self->{fieldFlags} = "(";

        for(my $i = 0; $i <= $#flags; ++$i)
        {
            my $flag = $flags[$i];

            $flag =~ s/ //g;
            $flag =~ s/\t//g;
            $flag =~ s/\n//g;

            if($i == 0 && $i != $#flags)
            {
                $self->{fieldFlags} .= "Field::".$flag." |";
                
                next;
            }

            if($i == $#flags)
            {
                if($i != 0)
                {
                    $self->{fieldFlags} .= " Field::".$flag;
                }
                else
                {
                    $self->{fieldFlags} .= "Field::".$flag;
                }

                next;
            }

            $self->{fieldFlags} .= " Field::".$flag." |";
        }
    
        $self->{fieldFlags} .= ")";
    }


    $self->{Fielddescription} = $self->{description};
    my $safe_field_desc = $self->{description};
    $safe_field_desc =~ s/"/\\\\\\"/g;
    $safe_field_desc =~ s/\n/\\n/g;
    $self->{SafeFielddescription} = $safe_field_desc;

    if($self->{CapsFieldtypeClean} =~ m/Ptr$/)
    {
        $self->{isPtrField} = "true";
    }
    else
    {
        $self->{isPtrField} = "false";
    }


    $self->{writePushToField}            = "false";
    $self->{writeInsertIntoMField}       = "false";
    $self->{writeReplaceInMFieldIndex}   = "false";
    $self->{writeReplaceInMFieldObject}  = "false";
    $self->{writeRemoveFromMFieldIndex}  = "false";
    $self->{writeRemoveFromMFieldObject} = "false";
    $self->{writeClearField}             = "false";

    
    if($self->{pushToField} eq "")
    {
        if($self->{pushToFieldAs} eq "")
        {
            $self->{pushToField} = "pushTo".$self->{Fieldname};
        }
        else
        {
            $self->{pushToField} = $self->{pushToFieldAs};
        }

        $self->{writePushToField} = "true";
    }

    if($self->{insertIntoMField} eq "")
    {
        if($self->{insertIntoMFieldAs} eq "")
        {
            $self->{insertIntoMField} = "insertInto".$self->{Fieldname};
        }
        else
        {
            $self->{insertIntoMField} = $self->{insertIntoMFieldAs};
        }

        $self->{writeInsertIntoMField} = "true";
    }

    if($self->{replaceInMFieldIndex} eq "")
    {
        if($self->{replaceInMFieldIndexAs} eq "")
        {
            $self->{replaceInMFieldIndex} = "replaceIn".$self->{Fieldname};
        }
        else
        {
            $self->{replaceInMFieldIndex} = $self->{replaceInMFieldIndexAs};
        }

        $self->{writeReplaceInMFieldIndex} = "true";
    }

    if($self->{replaceInMFieldObject} eq "")
    {
        if($self->{replaceInMFieldObjectAs} eq "")
        {
            $self->{replaceInMFieldObject} = "replaceIn".$self->{Fieldname};
        }
        else
        {
            $self->{replaceInMFieldObject} = $self->{replaceInMFieldObjectAs};
        }

        $self->{writeReplaceInMFieldObject} = "true";
    }

    if($self->{removeFromMFieldIndex} eq "")
    {
        if($self->{removeFromMFieldIndexAs} eq "")
        {
            $self->{removeFromMFieldIndex} = "removeFrom".$self->{Fieldname};
        }
        else
        {
            $self->{removeFromMFieldIndex} = $self->{removeFromMFieldIndexAs};
        }
        
        $self->{writeRemoveFromMFieldIndex} = "true";
    }

    if($self->{removeFromMFieldObject} eq "")
    {
        if($self->{removeFromMFieldObjectAs} eq "")
        {
            $self->{removeFromMFieldObject}= "removeFrom".$self->{Fieldname};
        }
        else
        {
            $self->{removeFromMFieldObject}= $self->{removeFromMFieldObjectAs};
        }

        $self->{writeRemoveFromMFieldObject} = "true";
    }

    if($self->{clearField} eq "")
    {
        if($self->{clearFieldAs} eq "")
        {
            $self->{clearField} = "clear".$self->{Fieldname};
        }
        else
        {
            $self->{clearField} = $self->{clearFieldAs};
        }

        $self->{writeClearField} = "true";
    }

    if($self->{removeTo} ne "")
    {
        $self->{removeToSet} = "true";
    }

    if($self->isPtrField() eq "true")
    {
        if($fc->isSystemComponent() eq "true")
        {
            $self->{FieldClassInclude} = "OSG"
        }
        else
        {
            $self->{FieldClassInclude} = "OpenSG/OSG"
        }

        $self->{FieldClassInclude} .= $self->{FieldtypeCapsClean};
        $self->{FieldClassInclude} =~ s/Ptr$//;
        $self->{FieldClassInclude} =~ s/Parent//;
        $self->{FieldClassInclude} .= ".h";
    }

    $self->{FieldDefaultHeader} = $self->{defaultHeader};
}

package OSGContainerWriter;
use strict;

#%OSGContainerWriter::isWriterIf = ();

#

sub new
{
    my $class       = shift;
    my $isDecorator = shift;

    my $self        = {};

    my %writerIf    = ();
    my $writerIfRef = \%writerIf;

    $writerIf{'Decorator'} = $isDecorator;
    $writerIf{'decorator'} = $isDecorator;

    $self->{writerDefs} = $writerIfRef;

    bless $self, $class
}

sub processFieldLoop
{
    my $linesRef      = shift;
    my $destRef       = shift;
    my $fc            = shift;
    my $fieldArrayRef = shift;
    
    for my $field (@$fieldArrayRef)
    {
#        print "process Field $field->{name} ($field->{Fieldname})\n";

        my $bSkipCurrent = 0;
        my @aSkipCurrent = ();
        
        for my $loopLine (@$linesRef)
        {
            if($loopLine =~ m/\@\@if[ \t]*(!|)([A-Za-z]*)/)
            {
                push(@aSkipCurrent, $bSkipCurrent);
            
                if($aSkipCurrent[$#aSkipCurrent] == 0)
                {
                    if(exists $field->{$2})
                    {
                        if($field->{$2} eq "true")
                        {
                            $bSkipCurrent = 0;
                        }
                        else
                        {
                            $bSkipCurrent = 1;
                        }

                        if($1 eq "!")
                        {
                            $bSkipCurrent = 1 - $bSkipCurrent;
                        }
                    }
                    elsif(exists $fc->{$2})
                    {
                        if($fc->{$2} eq "true")
                        {
                            $bSkipCurrent = 0;
                        }
                        else
                        {
                            $bSkipCurrent = 1;
                        }

                        if($1 eq "!")
                        {
                            $bSkipCurrent = 1 - $bSkipCurrent;
                        }
                    }
                    else
                    {
                        print "Warning unknown if val $2\n";
                        
                        $bSkipCurrent = 2;
                    }
                }
            
#        print "##$1\n";
#        print "##$2\n";
#        print "##$bSkipCurrent\n";
            
                if($bSkipCurrent != 2)
                {
                    next;
                }
            }
            
            if($loopLine =~ m/\@\@else/)
            {
                if($bSkipCurrent != 2)
                {
                    if($aSkipCurrent[$#aSkipCurrent] == 0)
                    {
                        $bSkipCurrent = 1 - $bSkipCurrent;
                    }
                    
                    next;
                }
            }
            
            if($loopLine =~ m/\@\@endif/)
            {
                my $doNext = 1;
                
                if($bSkipCurrent == 2)
                {
                    $doNext = 0;
                }
                
                $bSkipCurrent = pop(@aSkipCurrent);
                
                if($doNext == 1)
                {
                    next;
                }
            }
            
            if($bSkipCurrent == 1)
            {
                next;
            }

            my $tmpLine = $loopLine;
 
            while($tmpLine =~ m/@\?([^\?@]*)\?@/)
            {
                my $lookup = $1;
                
                if(exists $field->{$lookup})
                {
                    $tmpLine =~ s/@\?([^\?@]*)\?@/$field->{$lookup}/;
                }
                else
                {
                    print "error unknow $lookup\n";
                    $tmpLine =~ s/@\?([^\?@]*)\?@/@!$lookup!@/;
                }
            }
           
#            $tmpLine =~ s/@\?([^!@]*)\?@/$field->{$1}/g;
            
#            printf $tmpLine;

            push(@$destRef, $tmpLine);
        }
    }
}

sub init
{
    my $self    = shift;
    my $fc      = shift;
    my $inFile  = shift;
    my $outFile = shift;

    open(INPUT, "cat $inFile | ");

    my $bSkipCurrent = 1;
    my @aSkipCurrent = ();
    
    my @inLines = ();
    
    my @linesA = ();
    
    while(<INPUT>)
    {
        if(m/^char \*[^_]*_cpp\[\]=\{/ || 
           m/^char \*[^_]*_h\[\]=\{/   ||
           m/^char \*[^_]*_inl\[\]=\{/  )
        {
            $bSkipCurrent = 0;
            next;
        }

#        print "IN : $_";

        if(m/\@\@if[ \t]*(!|)([A-Za-z]*)/)
        {
            push(@aSkipCurrent, $bSkipCurrent);
            
            if($aSkipCurrent[$#aSkipCurrent] == 0)
            {
                if(exists $fc->{$2})
                {
                    if($fc->{$2} eq "true")
                    {
                        $bSkipCurrent = 0;
                    }
                    else
                    {
                        $bSkipCurrent = 1;
                    }
                    
                    if($1 eq "!")
                    {
                        $bSkipCurrent = 1 - $bSkipCurrent;
                    }
                }
                elsif (exists ${$self->{writerDefs}}{$2})
                {
                    if(${$self->{writerDefs}}{$2} eq "true")
                    {
                        $bSkipCurrent = 0;
                    }
                    else
                    {
                        $bSkipCurrent = 1;
                    }

                    if($1 eq "!")
                    {
                        $bSkipCurrent = 1 - $bSkipCurrent;
                    }
                }
                else
                {
                    if(exists $OSGField::isPerFieldIf{$2})
                    {
                        $bSkipCurrent = 2;
                    }
                    else
                    {
                        print "Warning unknown FC if val $2\n";
                        
                        $bSkipCurrent = 2;
                    }
                }
            }
            
#        print "##$1\n";
#        print "##$2\n";
#        print "##$bSkipCurrent\n";
            
            if($bSkipCurrent != 2)
            {
                next;
            }
        }
        
        if(m/\@\@else/)
        {
            if($bSkipCurrent != 2)
            {
                if($aSkipCurrent[$#aSkipCurrent] == 0)
                {
                    $bSkipCurrent = 1 - $bSkipCurrent;
                }
                
                next;
            }
        }
        
        if(m/\@\@endif/)
        {
            my $doNext = 1;
            
            if($bSkipCurrent == 2)
            {
                $doNext = 0;
            }
            
            $bSkipCurrent = pop(@aSkipCurrent);
            
            if($doNext == 1)
            {
                next;
            }
        }
        
        if($bSkipCurrent == 1)
        {
            next;
        }
        
        if(m/\@\@FieldIdsAndMasksDecl\@\@/)
        {
            $fc->addFieldIdsAndMasksDecl(\@linesA);
            next;
        }

        if(m/\@\@AdditionalIncludes\@\@/)
        {
            $fc->addAdditionaIncludes(\@linesA);
            next;
        }

        

        while($_ =~ m/@!([^!@]*)!@/)
        {
            my $lookup = $1;

            if($1 =~ m/([^:]*):([0-9]*)/)
            {
#                print "Foo $1 | $2\n";

                $lookup = $1;
            }

            if(exists $fc->{$lookup})
            {
                $_ =~ s/@!([^!@]*)!@/$fc->{$lookup}/;
            }
            else
            {
                $_ =~ s/@!([^!@]*)!@/@\?$lookup\?@/;
            }
        }

        $_ =~ s/^\"//;
        $_ =~ s/\",[ \t]*$//;
        $_ =~ s/\\\\/\\/g;
        $_ =~ s/\/\/\"/\/\//g;

        $_ =~ s/\\\"/\"/g;      
#"       
#        printf "$_";
        push(@linesA, $_);
    }
    
    pop(@linesA);
    
    my @loopLines;
    my $bInFLoop = 0;
    my $bInSFLoop = 0;
    my $bInMFLoop = 0;

    my @linesB = ();
    
    for my $line (@linesA)
    {   

        ## Field Loop

        if($line =~ /\@\@EndFieldLoop\@\@/)
        {
            $bInFLoop = 0;
            
            processFieldLoop(\@loopLines, \@linesB, $fc, $fc->{fields});
            
            @loopLines = ();

            next;
        }
        
        if($bInFLoop == 1)
        {
            push(@loopLines, $line);
            next;
        }
        
        if($line =~ /\@\@BeginFieldLoop\@\@/)
        {
            $bInFLoop = 1;
            next;
        }

        ## SField Loop

        if($line =~ /\@\@EndSFFieldLoop\@\@/)
        {
            $bInSFLoop = 0;
            
            processFieldLoop(\@loopLines, \@linesB, $fc, $fc->{SFields});
            
            @loopLines = ();

            next;
        }
        
        if($bInSFLoop == 1)
        {
            push(@loopLines, $line);
            next;
        }
        
        if($line =~ /\@\@BeginSFFieldLoop\@\@/)
        {
            $bInSFLoop = 1;
            next;
        }

        ## MField Loop

        if($line =~ /\@\@EndMFFieldLoop\@\@/)
        {
            $bInMFLoop = 0;
            
            processFieldLoop(\@loopLines, \@linesB, $fc, $fc->{MFields});
            
            @loopLines = ();

            next;
        }
        
        if($bInMFLoop == 1)
        {
            push(@loopLines, $line);
            next;
        }
        
        if($line =~ /\@\@BeginMFFieldLoop\@\@/)
        {
            $bInMFLoop = 1;
            next;
        }
        
        if($line =~ m/@\?([^\?@]*)\?@/)
        {
            print "Error unknow lookup $1\n";
        }

        push(@linesB, $line);
    }
    
    open(OUT, "> $outFile");
    
    for my $oline (@linesB)
    {
        printf OUT $oline;
    }
    
    close(OUT);
}

package main;
use XML::Parser;
use Getopt::Long;

sub usage
{
    print "Usage: fcdEdit -d file.fcd -t file.ftd -r root -bfh\n";
    print "  -d file.fcd: load the field container description\n";
    print "  -b write the field container base code files\n";
    print "  -f write the field container code files\n";
    print "  -p base code files output path\n";
    print "  -v dump read fieldcontainer\n";
    print "  -r root path\n";
    print "  -c enabled 1.x compat\n";
    print "  -h print usage\n";

    exit;
}

sub inputError
{
    my $rootPath = shift;
    my $file     = shift;

    print "Error could not find file $file tried path $rootPath \n";
    exit;
}

sub fixPath
{
    my $rootPath = shift;
    my $fileRef  = shift;

    if(! -r $rootPath.$$fileRef)
    {
        inputError($rootPath, $$fileRef);
    }
    else
    {
        $$fileRef = $rootPath.$$fileRef;
    }
}

my $writeBase  = "false";
my $writeFC    = "false";
my $writerPath = "";
my $rootPath   = "";
my $verbose    = -1;
my $inFile;

my $bArg;
my $fArg;
my $hArg;

GetOptions("d=s" => \$inFile,
           "b"   => \$bArg,
           "f"   => \$fArg,
           "p=s" => \$writerPath,
           "r=s" => \$rootPath,
           "v:i" => \$verbose,
           "h"   => \$hArg,
           "c"   => \$enableCompat);

if(defined $bArg)
{
    $writeBase = "true";
}

if(defined $fArg)
{
    $writeFC = "true";
}


#print "d : $inFile\n";
#print "b : $writeBase\n";
#print "f : $writeFC\n";
#print "p : $writerPath\n";
#print "v : $verbose\n";
#print "h : $hArg\n";

#print "c : $enableCompat\n";


if(defined $hArg)
{
    usage();
}

if(! defined $inFile)
{
    print "error no fcd file given\n";
    usage();
}

if(! -r $inFile)
{
    print "error could not access file $inFile\n";
    usage();
}

if($writerPath ne "" && (! -r $writerPath || ! -d $writerPath))
{
    print "error could not access path $writerPath\n";
    usage();
}

if(($writerPath ne "") && (! ($writerPath =~ m/\/$/)))
{
    $writerPath .= "/";
}

if($rootPath eq "")
{
    if(defined $ENV{'OSG_ROOT'})
    {
        $rootPath = $ENV{'OSG_ROOT'};
    }
    else # Use Script path to guess root path
    {
        $rootPath = $0;
        $rootPath =~ s/Tools[\/]+fcdProcess[\/]+fcdProcess.pl//;
    }
}

if(($rootPath ne "") && (! ($rootPath =~ m/\/$/)))
{
    $rootPath .= "/Tools/fcdProcess/";
}
else
{
    $rootPath .= "Tools/fcdProcess/";
}

fixPath($rootPath, \$baseTmplCpp);
fixPath($rootPath, \$baseTmplH);
fixPath($rootPath, \$baseTmplInl);
fixPath($rootPath, \$fieldImpH);
fixPath($rootPath, \$fcTmplCpp);
fixPath($rootPath, \$fcTmplH);
fixPath($rootPath, \$fcTmplInl);

if($verbose >= 0)
{
    print "Found : \n";
    print "$baseTmplCpp\n";
    print "$baseTmplH\n";
    print "$baseTmplInl\n";
    print "$fieldImpH\n";
    print "$fcTmplCpp\n";
    print "$fcTmplH\n";
    print "$fcTmplInl\n";
}

my $parser = new XML::Parser( Handlers =>
                              { Start => \&start_element,
                                End   => \&end_element,
                                Char  => \&characters, 
                              },
                              ParseParamEnt => 1
                            );


$parser->parsefile($inFile);

open(FCD_XML_FILE, $inFile);
my $line;
while ( $line = <FCD_XML_FILE> )
{
    chomp($line);
    # This triple backslash is to defeat post processing in
    # OSGContainerWriter::init().
    $line =~ s/"/\\\\\\"/g;
    $gfcdXml .= "\"$line\\n\"\n";
}
close(FCD_XML_FILE);

$gfc->finalize();
$gfc->{Fcdxml} = $gfcdXml;

if($verbose >= 1)
{
    $gfc->dumpValues();
    printf "write to $writerPath\n";
}

if($writeBase eq "true")
{
    my $base_h_writer   = new OSGContainerWriter("false");
    my $base_cpp_writer = new OSGContainerWriter("false");
    my $base_inl_writer = new OSGContainerWriter("false");
    my $fields_h_writer = new OSGContainerWriter("false");

    $gfc->setupFieldContainer();

    my $outFile = $writerPath.$filePrefix.$gfc->{name}."Base".$decFileSuffix;

    $base_h_writer  ->init($gfc, 
                           $baseTmplH,   
                           $outFile);
    
    $outFile = $writerPath.$filePrefix.$gfc->{name}."Base".$impFileSuffix;

    $base_cpp_writer->init($gfc, 
                           $baseTmplCpp, 
                           $outFile);

    $outFile = $writerPath.$filePrefix.$gfc->{name}."Base".$inlFileSuffix;

    $base_inl_writer->init($gfc, 
                           $baseTmplInl, 
                           $outFile);
    
    $outFile = $writerPath.$filePrefix.$gfc->{name}."Fields".$decFileSuffix;

    $fields_h_writer->init($gfc, 
                           $fieldImpH, 
                           $outFile);

    if($gfc->{isDecoratable} eq "true")
    {
        my $base_h_decwriter   = new OSGContainerWriter("true");
        my $base_cpp_decwriter = new OSGContainerWriter("true");
        my $base_inl_decwriter = new OSGContainerWriter("true");
        my $fields_h_decwriter = new OSGContainerWriter("true");

        $gfc->setupDecorator();

        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "DecoratorBase".$decFileSuffix;
        
        $base_h_decwriter  ->init($gfc, 
                                  $baseTmplH,   
                                  $outFile);

        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "DecoratorBase".$impFileSuffix;

        $base_cpp_decwriter->init($gfc, 
                                  $baseTmplCpp, 
                                  $outFile);

        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "DecoratorBase".$inlFileSuffix;

        $base_inl_decwriter->init($gfc, 
                                  $baseTmplInl, 
                                  $outFile);

        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "DecoratorFields".$decFileSuffix;

        $fields_h_decwriter->init($gfc, 
                                  $fieldImpH, 
                                  $outFile);
    }
}

if($writeFC eq "true")
{
    my $fc_h_writer   = new OSGContainerWriter("false");
    my $fc_cpp_writer = new OSGContainerWriter("false");
    my $fc_inl_writer = new OSGContainerWriter("false");

    $gfc->setupFieldContainer();

    my $outFile = $writerPath.$filePrefix.$gfc->{name}.$decFileSuffix;

    $fc_h_writer  ->init($gfc, 
                         $fcTmplH,
                         $outFile);

    $outFile = $writerPath.$filePrefix.$gfc->{name}.$impFileSuffix;

    $fc_cpp_writer->init($gfc, 
                         $fcTmplCpp,
                         $outFile);

    $outFile = $writerPath.$filePrefix.$gfc->{name}.$inlFileSuffix;

    $fc_inl_writer->init($gfc, 
                         $fcTmplInl, 
                         $outFile);

    if($gfc->{isDecoratable} eq "true")
    {
        my $fc_h_decwriter   = new OSGContainerWriter("true");
        my $fc_cpp_decwriter = new OSGContainerWriter("true");
        my $fc_inl_decwriter = new OSGContainerWriter("true");

        $gfc->setupDecorator();
        
        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "Decorator".$decFileSuffix;

        $fc_h_decwriter  ->init($gfc, 
                                $fcTmplH,
                                $outFile);

        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "Decorator".$impFileSuffix;

        $fc_cpp_decwriter->init($gfc, 
                                $fcTmplCpp,
                                $outFile);

        $outFile = $writerPath.$filePrefix.$gfc->{name}.
            "Decorator".$inlFileSuffix;

        $fc_inl_decwriter->init($gfc, 
                                $fcTmplInl, 
                                $outFile);
    }
}

exit;





