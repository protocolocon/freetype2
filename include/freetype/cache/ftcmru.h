/***************************************************************************/
/*                                                                         */
/*  ftcmru.h                                                               */
/*                                                                         */
/*    Simple MRU list-cache (specification).                               */
/*                                                                         */
/*  Copyright 2000-2001, 2003 by                                           */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


  /*************************************************************************/
  /*                                                                       */
  /* An MRU is a list that cannot hold more than a certain number of       */
  /* elements (`max_elements').  All elements in the list are sorted in    */
  /* least-recently-used order, i.e., the `oldest' element is at the tail  */
  /* of the list.                                                          */
  /*                                                                       */
  /* When doing a lookup (either through `Lookup()' or `Lookup_Node()'),   */
  /* the list is searched for an element with the corresponding key.  If   */
  /* it is found, the element is moved to the head of the list and is      */
  /* returned.                                                             */
  /*                                                                       */
  /* If no corresponding element is found, the lookup routine will try to  */
  /* obtain a new element with the relevant key.  If the list is already   */
  /* full, the oldest element from the list is discarded and replaced by a */
  /* new one; a new element is added to the list otherwise.                */
  /*                                                                       */
  /* Note that it is possible to pre-allocate the element list nodes.      */
  /* This is handy if `max_elements' is sufficiently small, as it saves    */
  /* allocations/releases during the lookup process.                       */
  /*                                                                       */
  /*************************************************************************/


#ifndef __FTCMRU_H__
#define __FTCMRU_H__


#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef FREETYPE_H
#error "freetype.h of FreeType 1 has been loaded!"
#error "Please fix the directory search order for header files"
#error "so that freetype.h of FreeType 2 is found first."
#endif


FT_BEGIN_HEADER

  typedef struct FTC_MruNodeRec_*              FTC_MruNode;

  typedef struct FTC_MruNodeRec_
  {
    FTC_MruNode   next;
    FTC_MruNode   prev;

  } FTC_MruNodeRec;


  FT_EXPORT( void )
  FTC_MruNode_Prepend( FTC_MruNode  *plist,
                       FTC_MruNode   node );

  FT_EXPORT( void )
  FTC_MruNode_Up( FTC_MruNode  *plist,
                  FTC_MruNode   node );

  FT_EXPORT( void )
  FTC_MruNode_Remove( FTC_MruNode  *plist,
                      FTC_MruNode   node );


  typedef struct FTC_MruListRec_*              FTC_MruList;

  typedef struct FTC_MruListClassRec_ const *  FTC_MruListClass;

  typedef FT_Int       (*FTC_MruNode_CompareFunc)( FTC_MruNode  node,
                                                   FT_Pointer   key );

  typedef FT_Error     (*FTC_MruNode_InitFunc)( FTC_MruNode  node,
                                                FT_Pointer    key,
                                                FT_Pointer    data );

  typedef FT_Error     (*FTC_MruNode_ResetFunc)( FTC_MruNode  node,
                                                 FT_Pointer   key,
                                                 FT_Pointer   data );

  typedef void         (*FTC_MruNode_DoneFunc)( FTC_MruNode  node,
                                                FT_Pointer   data );

  typedef struct FTC_MruListClassRec_
  {
    FT_UInt                   node_size;
    FTC_MruNode_CompareFunc   node_compare;
    FTC_MruNode_InitFunc      node_init;
    FTC_MruNode_ResetFunc     node_reset;
    FTC_MruNode_DoneFunc      node_done;

  } FTC_MruListClassRec;


  typedef struct FTC_MruListRec_
  {
    FT_UInt                  num_nodes;
    FT_UInt                  max_nodes;
    FTC_MruNode              nodes;
    FT_Pointer               data;
    FTC_MruListClassRec      clazz;
    FT_Memory                memory;

  } FTC_MruListRec;


  FT_EXPORT( void )
  FTC_MruList_Init( FTC_MruList       list,
                    FTC_MruListClass  clazz,
                    FT_UInt           max_nodes,
                    FT_Pointer        data,
                    FT_Memory         memory );

  FT_EXPORT( void )
  FTC_MruList_Reset( FTC_MruList  list );


  FT_EXPORT( void )
  FTC_MruList_Done( FTC_MruList  list );


  FT_EXPORT( FTC_MruNode )
  FTC_MruList_Lookup( FTC_MruList   list,
                      FT_Pointer    key );

  FT_EXPORT( void )
  FTC_MruList_Up( FTC_MruList    list,
                  FTC_MruNode    node );

  FT_EXPORT( FT_Error )
  FTC_MruList_New( FTC_MruList    list,
                   FT_Pointer     key,
                   FTC_MruNode   *anode );

  FT_EXPORT( void )
  FTC_MruList_Remove( FTC_MruList  list,
                      FTC_MruNode  node );

  FT_EXPORT( void )
  FTC_MruList_RemoveSelection( FTC_MruList              list,
                               FTC_MruNode_CompareFunc  select,
                               FT_Pointer               key );
 /* */

FT_END_HEADER


#endif /* __FTCMRU_H__ */


/* END */