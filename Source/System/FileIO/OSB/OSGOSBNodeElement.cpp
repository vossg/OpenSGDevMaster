/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2006 by the OpenSG Forum                  *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include "OSGOSBNodeElement.h"

#include "OSGOSBRootElement.h"
#include "OSGNode.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBNodeElement                                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBNodeElement>
    OSBNodeElement::_regHelper =
        OSBElementRegistrationHelper<OSBNodeElement>("Node");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBNodeElement::OSBNodeElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBNodeElement::~OSBNodeElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBNodeElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBNodeElement::read [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh        = editRoot()->getReadHandler();
    UInt8              fcPtrType;
    UInt16             version;

    rh->getValue(fcPtrType);
    rh->getValue(version  );

    OSG_OSB_LOG(("OSBNodeElement::read: version: [%u]\n", version));

    if(fcPtrType != OSBCommonElement::FCPtrNode)
    {
        FFATAL(("OSBNodeElement::read: fcPtrType has unexpected value.\n"));

        skipFields();
        return;
    }

    NodeUnrecPtr node = Node::create();

    setContainer(node);

    if(version == OSGOSBHeaderVersion100)
    {
        std::string    fieldName;
        std::string    fieldTypeName;
        UInt32         fieldSize;
        PtrFieldListIt ptrFieldIt;
    
        while(readFieldHeader("", fieldName, fieldTypeName, fieldSize))
        {
            // some fields need to be duplicated for the two replacement chunks
            if(fieldName == "volume")
            {
                // parent fields are ignored
                UInt32 fieldType = 0;
                rh->getValue(fieldType);

                switch(fieldSize)
                {
                    case 30:
                    {
                        UInt16 sState;
                        Pnt3f  vMin;
                        Pnt3f  vMax;
                        
                        rh->getValue(sState );

                        rh->getValue(vMin[0]);
                        rh->getValue(vMin[1]);
                        rh->getValue(vMin[2]);
                        rh->getValue(vMax[0]);
                        rh->getValue(vMax[1]);
                        rh->getValue(vMax[2]);

                        node->editVolume().setState (sState    );
                        node->editVolume().setBounds(vMin, vMax);
                    }
                    break;

                    case 22: 
                    {
                        UInt16 sState;
                        Pnt3f  vCenter;
                        Real32 fRadius;

                        rh->getValue(sState    );

                        rh->getValue(vCenter[0]);
                        rh->getValue(vCenter[1]);
                        rh->getValue(vCenter[2]);
                        rh->getValue(fRadius);

                        node->editVolume().setState (sState              );
                        node->editVolume().setBounds(vCenter[0] - fRadius,
                                                     vCenter[1] - fRadius,
                                                     vCenter[2] - fRadius,
                                                     vCenter[0] + fRadius,
                                                     vCenter[1] + fRadius,
                                                     vCenter[2] + fRadius);
                    }
                    break;

                    default:
                        fprintf(stderr, 
                                "unknown volume type with size %d, skipping\n",
                                fieldSize                                     );

                        rh->skip(fieldSize - sizeof(UInt32)); 

                        break;
                }
            }    
            else
            {
                readFieldContent(fieldName, 
                                 fieldTypeName, 
                                 fieldSize, "", 
                                 ptrFieldIt   );
            }
        }
    }
    else
    {
        readFields("", "");
    }
}

void
OSBNodeElement::postRead(void)
{
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBNodeElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBNodeElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBNodeElement::write(void)
{
    OSG_OSB_LOG(("OSBNodeElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBNodeElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(OSBCommonElement::FCPtrNode);
    wh->putValue(getVersion()               );

    const OSBRootElement *root         = getRoot();
          Node           *node         = dynamic_cast<Node*>(getContainer());
          std::string     doSkipFields = "";

    if(node->getVolume ().isStatic         () == false &&
       node->getVolume ().isInfinite       () == false &&
       root->getOptions().forceVolumeExport() == false  )
    {
        doSkipFields += "'volume'";
    }

    writeFields(doSkipFields, true);
}
