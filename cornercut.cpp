#include <stdio.h>

#include <iostream>
#include <vector>
#include <set>
#include <array>

using namespace std;

struct Node
{
    int id;
    bool corner  = false;
    bool removed = false;
};

struct Face
{
    std::array<int,3> nodes;
};

void cornercuts( vector<Node> &nodes, vector<Face> &faces)
{
    Face newface;

    if( nodes.size() == 3) {
        newface.nodes = { nodes[0].id, nodes[1].id, nodes[2].id};
        faces.push_back(newface);
        return;
    }

    int numnodes = nodes.size();

    std::set<int> corners;

    for( int i = 0; i < numnodes; i++) {
        nodes[i].removed = false;
        if (nodes[i].corner ) corners.insert(i);
    }

    while( !corners.empty() ) {
          int p0 = *corners.begin();
          int p1 = (p0+1)%numnodes;
          int p2 = (p0+numnodes-1)%numnodes;
          int v0 = nodes[p0].id;
          int v1 = nodes[p1].id;
          int v2 = nodes[p2].id;
          newface.nodes = {v0, v1, v2};
          faces.push_back(newface);
	  corners.erase(p0);
	  corners.erase(p1);
	  corners.erase(p2);
          nodes[p1].corner  = true;
          nodes[p2].corner  = true;
	  nodes[p0].removed = true;
    }

    vector<Node> newnodes;
    for( int i  = 0; i < numnodes; i++) {
        if( nodes[i].removed == false)
            newnodes.push_back( nodes[i] );
    }

    nodes = newnodes;
    cornercuts( nodes, faces);
}


int main()
{
    int n = 17;

    vector<Node> nodes(n);

    for( int i = 0; i < n; i++)
        nodes[i].id = i;

    nodes[0].corner = true;
    nodes[5].corner = true;
    nodes[8].corner = true;
    nodes[13].corner = true;

    vector<Face> faces;

    cornercuts(nodes, faces);

    for( auto f : faces)
	    cout << f.nodes[0] << " " << f.nodes[1] << "  " << f.nodes[2] << endl;

}

