//Question: https://www.spoj.com/problems/INVENT/

#include <cstdio>
#include <algorithm>

#define MAXN 100000 

using namespace std;

struct edge {
    int source;
    int destination ;
    int weight;
};

bool operator <( edge a, edge b ) {
    return a.weight < b.weight;
}

long long int rank[ MAXN + 1 ], num[ MAXN + 1 ], Parent[ MAXN + 1 ];

void makeSet( int x ) {
    Parent[ x ] = x;
    rank[ x ] = 1;
    num[ x ] = 1;
}

int findSet( int x ) {
    if ( x == Parent[ x ] ) {
        return x;
    }
    else {
        return ( Parent[ x ] = findSet( Parent[ x ] ) );
    }
}

void Union( int x, int y ) {
    x = findSet( x );
    y = findSet( y );
    if ( rank[ x ] > rank[ y ] ) {
        Parent[ y ] = x;
        num[ x ] += num[ y ];
    }
    else {
        Parent[ x ] = y;
        num[ y ] += num[ x ];
        if ( rank[ x ] == rank[ y ] ) {
            rank[ y ] += 1;
        }
    }
}

int main() {
    int Nodes, s, d, tree;
    unsigned long long int sum;
    edge array[ MAXN + 1 ];
    scanf( "%d", &tree );
    while ( tree-- ) {
        sum = 0;
        scanf( "%d", &Nodes );
        for (int  i = 0; i < Nodes - 1; ++i ) {
            scanf( "%d%d%d", &array[ i ].source, &array[ i ].destination, &array[ i ].weight );
            makeSet( array[ i].source);
            makeSet( array[ i ].destination );
        }
        sort( array, array + Nodes - 1 );
        for ( int i = 0; i < Nodes - 1; ++i ) {
            s = findSet( array[ i ].source );
            d = findSet( array[ i ].destination );
            if ( s != d ) {
                sum += num[ s ] * num[ d ] * ( array[ i ].weight + 1 );
                Union( array[ i ].source, array[ i ].destination );
            }
        }

        printf( "%lld\n", sum - Nodes + 1 );
    }
    return 0;
}