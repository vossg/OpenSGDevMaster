/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *                     contact: danielg@iastate.edu                          *
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


#include "OSGRadixSort.h"

OSG_BEGIN_NAMESPACE

void RadixSort(UInt32 size, const MFReal32 &floats, MFUInt32 &indices)
{
    static UInt32   sHistogram[256*4];
    static UInt32   sOffset   [256  ];
    static MFUInt32 indices2;
//    static int previousSize(0);

    if(indices2.size() < size)
    { //resize our secondary indices vector if needed.
        indices2.resize(size);

        for(UInt32 i = 0; i < size; ++i)    
        {
            indices [i] = i;
            indices2[i] = i;
        }
    }

//    previousSize = size;

    const UInt32* input = reinterpret_cast<const UInt32 *>(&floats[0]);

        // Clear counters           
    memset(&sHistogram[0], 0, 256 * 4 * sizeof(UInt32)); 
                                                    
    // Prepare for temporal coherence       
    Real32  PrevVal       = floats[indices[0]];        
    bool    AlreadySorted = true;  // Optimism... 
    UInt32 *index         = &indices[0];
                                                    
    /* Prepare to count */                          
    const UChar8* p = reinterpret_cast<const UChar8 *>(input);
    const UChar8* pe = &p[size * 4];                            

    UInt32 *h0= &sHistogram[0  ]; /* Histogram for first pass (LSB)*/     
    UInt32 *h1= &sHistogram[256]; /* Histogram for second pass*/      
    UInt32 *h2= &sHistogram[512]; /* Histogram for third pass*/       
    UInt32 *h3= &sHistogram[768]; /* Histogram for last pass (MSB)*/  
                                                                        
    while(p != pe)                                                        
    {                                                                   
        // Read input buffer in previous sorted order               
        Real32 Val = floats[*index++];                          

        // Check whether already sorted or not x                    
        if(Val < PrevVal)  // Early out
        { 
            AlreadySorted = false; 
            break; 
        } 

        // Update for next iteration            
        PrevVal = Val;                                  
                                                        
        // Create histograms                    
        h0[*p++]++; 
        h1[*p++]++; 
        h2[*p++]++; 
        h3[*p++]++; 
    }                                                   
                                                        
    /* If all input values are already sorted, we just have to return and
     * leave the previous list unchanged. That way the routine may take
     * advantage of temporal coherence, for example when used to sort
     * transparent faces. 
     */                 
    if(AlreadySorted) 
        return; 

    // Else there has been an early out and we must finish computing the
    // histograms  

    while(p != pe)                                                
    {                                                           
        // Continue to create histograms from where we left off 
        h0[*p++]++; 
        h1[*p++]++; 
        h2[*p++]++; 
        h3[*p++]++;         
    }

    
    // Compute #negative values involved if needed
    UInt32 NbNegativeValues = 0;

    // An efficient way to compute the number of negatives values we'll have
    // to deal with is simply to sum the 128 last values of the last
    // histogram. Last histogram because that's the one for the Most
    // Significant Byte, responsible for the sign. 128 last values because the
    // 128 first ones are related to positive numbers. 

    h3 = &sHistogram[768];

    for(UInt32 i = 128; i < 256; ++i) 
        NbNegativeValues += h3[i];  // 768 for last histogram, 128 for
                                    // negative part 

    // we index from these alternating arrays each pass, and they must be
    // swapped each time. To avoid having to copy all of the elements each
    // pass, we just use pointers to handle this 

    UInt32 *sortPtr  = &indices [0];
    UInt32 *sort2Ptr = &indices2[0];

    // Radix sort, j is the pass number (0=LSB, 3=MSB)
    for(UInt32 j = 0; j < 4; ++j)
    {
        // Should we care about negative values?
        if(j != 3)
        {
            // Here we deal with positive values only
            // Shortcut to current counters                         
            UInt32 *CurCount = &sHistogram[j << 8];                   
                                                                        
            // Reset flag. The sorting pass is supposed to be
            // performed. (default) 
            bool PerformPass = true;                    

            // Get first byte                               
            UChar8 UniqueVal = *((reinterpret_cast<const UChar8 *>(input)+j)); 
                                                                    
            // Check that byte's counter    
            if(CurCount[UniqueVal] == size)   
                PerformPass = false;  

            if(PerformPass == true)
            {
                // Create offsets
                sOffset[0] = 0;

                for(UInt32 i = 1; i < 256; ++i) 
                {
                    sOffset[i] = sOffset[i - 1] + CurCount[i - 1];
                }

                // Perform Radix Sort
                const UChar8* InputBytes = 
                    reinterpret_cast<const UChar8 *>(input);

                UInt32 *indexIt  =  sortPtr;
                UInt32 *indexEnd = &sortPtr[size];

                InputBytes += j;

                while(indexIt != indexEnd)
                {
                    UInt32 id = *indexIt++;

                    sort2Ptr[sOffset[InputBytes[id << 2]]++] = id;
                }

                // Swap pointers for next pass. Valid indices - the most
                // recent ones - are in sortPtr after the swap. 

                UInt32 *Tmp = sortPtr;  
                sortPtr     = sort2Ptr; 
                sort2Ptr    = Tmp;
            }
        }
        else
        {
            // This is a special case to correctly handle negative values
            /* Shortcut to current counters */                      
            UInt32 *CurCount = &sHistogram[j << 8];               

            /* Get first byte */                                    
            UChar8 UniqueVal = *((reinterpret_cast<const UChar8*>(input) + j)); 
                                                                
            if(CurCount[UniqueVal] != size)
            {
                // Create biased offsets, in order for negative numbers to be
                // sorted as well 
                sOffset[0] = NbNegativeValues; // First positive number takes
                                               // place after the negative
                                               // ones 

                // 1 to 128 for positive numbers 
                for(UInt32 i = 1; i < 128; ++i)   
                    sOffset[i] = sOffset[i-1] + CurCount[i-1];  

                // We must reverse the sorting order for negative numbers!
                sOffset[255] = 0;

                // Fixing the wrong order for negative values
                for(UInt32 i = 0; i < 127; ++i) 
                    sOffset[254 - i] = sOffset[255 - i] + CurCount[255 - i];

                // Fixing the wrong place for negative values
                for(UInt32 i = 128; i < 256; ++i) 
                    sOffset[i] += CurCount[i];  

                // Perform Radix Sort
                for(UInt32 i = 0; i < size; ++i)
                {
                    // Radix byte, same as above. AND is useless here (UInt32).
                    UInt32 Radix = input[sortPtr[i]] >> 24;   

                    if(Radix < 128) 
                    {
                        // Number is positive, same as above
                        sort2Ptr[sOffset[Radix]++] = sortPtr[i]; 
                    }
                    else 
                    {
                        // Number is negative, flip the sorting order
                        sort2Ptr[--sOffset[Radix]] = sortPtr[i]; 
                    }
                }
                // Swap pointers for next pass. Valid indices - the most
                // recent ones - are in sortPtr after the swap. 
                UInt32 *Tmp = sortPtr;  
                sortPtr     = sort2Ptr; 
                sort2Ptr    = Tmp;
            }
            else
            {
                // The pass is useless, yet we still have to reverse the order
                // of current list if all values are negative. 
                if(UniqueVal >= 128)
                {
                    for(UInt32 i = 0; i < size; i++)  
                        sort2Ptr[i] = sortPtr[size - i - 1];

                    // Swap pointers for next pass. Valid indices - the most
                    // recent ones - are in sortPtr after the swap. 
                    UInt32* Tmp = sortPtr;  
                    sortPtr     = sort2Ptr; 
                    sort2Ptr    = Tmp;
                }
            }
        } //end if (j!=3)
    } // end for (j<4...)
}// end of doRadixSort()

OSG_END_NAMESPACE
