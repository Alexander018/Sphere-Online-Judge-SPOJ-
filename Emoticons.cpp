//Question: https://www.spoj.com/problems/EMOTICON/

#include <stdio.h> 
#include <string.h> 

#include <algorithm> 
#include <iostream> 
#include <queue> 
using  namespace  std ;

int  m, n;

namespace  trie  {
const  int  N =  2007 ;
int  a [N][ 128 ], ind =  0 ;   
int  Prev [N];
bool  Leaf [N];  

void  clear () {//clears the trie basically starting as new 
    ind =  0 ;
    memset (a,  0 , sizeof a);
    memset (Prev,  0 , sizeof Prev);
    memset (Leaf,  0 , sizeof Leaf);
}

void  insert ( char  s []) {//insert to tire 
    int  u =  0 ;
    for  ( int  i =  0 ;  char  k =  s [i]; i++) {
        if  (! a [u][k])  a [u][k] = ++ind;
        u =  a [u][k];
    }
    Leaf [u] =  true ;
}

int  next ( int  u ,  char  k ) {//trie next
    for  ( int  i = u; i != - 1 ; i =  Prev [i])
        if  ( a [i][k])  return  a [i][k];
    return  0 ;
}

void  bfs () {//breath first search 
    queue< int > qu;
    qu . push ( 0 );
    Prev [ 0 ] = - 1 ;
    while  ( qu . size ()) {
        int  u =  qu . front ();
        qu . pop ();
        for  ( int  k =  0 ; k <  128 ; k++)
            if  ( int  v =  a [u][k]) {
                Prev [v] =  next ( Prev [u], k);
                Leaf [v] |=  Leaf [ Prev [v]];
                qu . push (v);
            }
    }
}
};   //end of trie 

int  solveHelp ( char  s []) {
    using  namespace  trie ;
    int  u =  0 , count =  0 ;
    for  ( int  i =  0 ;  s [i]; i++) {
        u =  next (u,  s [i]);
        if  ( Leaf [u]) {
            count++;
            u =  0 ;
        }
    }
    return  count;
}

void  solve () {
    for  ( int  i =  1 ; i <= m; i++) {
        char  s [ 123 ];// set size of line to 123 Note 80 doesnt work 
        cin.getline(s,123);//gets the string and the emoticons which is part of the string
        trie  :: insert (s);//inseet the string into the trie 
    }
    trie  :: bfs ();

    int  Sum =  0 ;
    for  ( int  i =  1 ; i <= n; i++) {
        char  s [ 123 ];
        cin.getline(s,123);//gets the string and the emoticons which is part of the string
        Sum +=  solveHelp (s);
    }
    cout << Sum << endl;
}

void  readln () {//reads line to discard the new line char 
    do  {
    }  while  ( getchar () !=  '\n'  );
}

int  main () {
    while(true) {//since I have to wait till both are zero just keep it running till they are 0
        scanf("%d%d", &m, &n);
        readln ();
        if  (m ==  0  && n ==  0 ) 
             return  0 ;//ends the program

        solve ();
        trie  :: clear ();//clears the trie to start a new since we could do it multiple times 
    }
}