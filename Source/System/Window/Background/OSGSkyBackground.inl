/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline const Vec3f *SkyBackground::selectTexCoords(
    const Vec3f *userTexCoords, TextureBaseChunk *texImage, UInt32 side)
{
    const Vec3f *returnValue = NULL;

    if(userTexCoords != NULL)
    {
        returnValue = userTexCoords;
    }
    else
    {
        if(getUseVRMLCubeTextureSemantics() == true)
        {
            if(texImage                  != NULL &&
               texImage->isCubeTexture() == true   )
            {
                returnValue = _defaultVRMLTexCoords[side];
            }
            else
            {
                returnValue = _defaultVRMLTexCoords[0];
            }
        }
        else
        {
            if(texImage                  != NULL &&
               texImage->isCubeTexture() == true   )
            {
                returnValue = _defaultTexCoords[side];
            }
            else
            {
                returnValue = _defaultTexCoords[0];
            }
        }
    }

    return returnValue;
}

OSG_END_NAMESPACE
