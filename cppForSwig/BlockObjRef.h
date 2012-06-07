////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Copyright (C) 2011-2012, Alan C. Reiner    <alan.reiner@gmail.com>        //
//  Distributed under the GNU Affero General Public License (AGPL v3)         //
//  See LICENSE or http://www.gnu.org/licenses/agpl.html                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef _BLOCKOBJREF_H_
#define _BLOCKOBJREF_H_


#include <iostream>
#include <vector>
#include <map>
#include <cassert>

#include "BtcUtils.h"
#include "BinaryData.h"
#include "BlockObj.h"



class BlockHeader;
class OutPoint;
class TxIn;
class TxOut;
class Tx;

class TxRef;






////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class TxRef
{
   friend class BlockDataManager_MMAP;

public:
   /////////////////////////////////////////////////////////////////////////////
   TxRef(void) : headerPtr_(NULL) {}
   TxRef(FileDataPtr fdr) : blkFilePtr_(fdr), headerPtr_(NULL) {}
     
   /////////////////////////////////////////////////////////////////////////////
   BinaryData         getThisHash(void) const;
   Tx                 getTxCopy(void) const;
   bool               isInitialized(void)  const;

   /////////////////////////////////////////////////////////////////////////////
   BlockHeader*       getHeaderPtr(void) const { return headerPtr_; }
   void               setHeaderPtr(BlockHeader* bh)   { headerPtr_ = bh; }
   FileDataPtr*       getBlkFilePtr(void) const { return blkFilePtr_; }
   
   /////////////////////////////////////////////////////////////////////////////
   bool               isMainBranch(void)  const;
   FileDataPtr        getBlkFileRef(void) { return blkFilePtr_; }
   void               setBlkFileRef(FileDataPtr b) { blkFilePtr_ = b; }
   uint32_t           getSize(void) const {  return blkFilePtr_.getNumBytes(); }

   /////////////////////////////////////////////////////////////////////////////
   BinaryData         serialize(void) const { return blkFilePtr_.getDataCopy(); }


   /////////////////////////////////////////////////////////////////////////////
   TxInRef            getTxInRef(int i);
   TxOutRef           getTxOutRef(int i);
   
   /////////////////////////////////////////////////////////////////////////////
   uint32_t           getBlockTimestamp(void);
   uint32_t           getBlockHeight(void);
   uint32_t           getBlockTxIndex(void);

private:
   FileDataPtr        blkFilePtr_;
   BlockHeader*       headerPtr_;
};

#endif
