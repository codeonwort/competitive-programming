// ID  : 699D (Fix a Tree)
// URL : https://codeforces.com/contest/699/problem/D

#include <iostream>
#include <vector>
using namespace std;

// Print debug output if 1
#define TEST 0

struct Vertex
{
    int id = -1;             // Starts from 1
    int parentId = -1;       // id of parent vertex
    int groupId = -1;        // Starts from 0
    bool visited = false;    // Used in two contexts (for dfs and for cycle detection)
    vector<int> neighborIds; // Undirected connectivity (excluding self-edge)
};

// Group = Graph
struct Group
{
    int anyMemberIndex = -1; // Any member vertex's element index in 'vertices'
    int rootId = -1;         // Root vertex's id. If cyclic, updated to any vertex's id in the cycle.
    bool cyclic = false;     // Contains a cycle? (At most one cycle exists by problem definition)
    int numMembers = 0;
};

// Data structures
vector<Vertex> vertices;
vector<Group> groups;

void dfs(int vertexIndex, int groupId)
{
    Vertex& v = vertices[vertexIndex];
    if (v.visited)
    {
        return;
    }

    v.visited = true;
    v.groupId = groupId;
    groups[groupId].numMembers += 1;
    for (int neighborId : v.neighborIds)
    {
        dfs(neighborId - 1, groupId);
    }
}

int main()
{
    int n;
    cin >> n;

    vertices.resize(n);
    for (int i=0; i<n; ++i)
    {
        vertices[i].id = i + 1;
        cin >> vertices[i].parentId;
    }

    for (int i=0; i<n; ++i)
    {
        int parentId = vertices[i].parentId;
        if (parentId != i+1)
        {
            vertices[i].neighborIds.push_back(parentId);
            vertices[parentId-1].neighborIds.push_back(i + 1);
        }
    }
    
    // Find isolated groups(graphs).
    int groupId = 0;
    for (int i=0; i<n; ++i)
    {
        if (!vertices[i].visited)
        {
            Group G;
            G.anyMemberIndex = i;
            groups.push_back(G);

            dfs(i, groupId);
            groupId += 1;
        }
    }
    const int numGroups = groupId;

#if TEST
    for (int j=0; j<numGroups; ++j)
    {
        cout << "group[" << j << "] : ";
        for (int i=0; i<n; ++i)
        {
            if (vertices[i].groupId == j)
            {
                cout << vertices[i].id << ' ';
            }
        }
        cout << endl;
    }
#endif

    // Find cyclic graphs.
    for (int i=0; i<n; ++i) vertices[i].visited = false;
    for (int j=0; j<numGroups; ++j)
    {
        Vertex v = vertices[groups[j].anyMemberIndex];
#if TEST
        cout << "cycle test for group(" << j << ") : v.id=" << v.id << endl;
#endif
        v.visited = true;
        while (v.parentId != v.id)
        {
            v = vertices[v.parentId - 1];
#if TEST
            cout << "v.id=" << v.id << endl;
#endif
            if (v.visited)
            {
                groups[j].cyclic = true;
                groups[j].anyMemberIndex = v.id - 1;
                break;
            }
            vertices[v.id-1].visited = true;
        }
        groups[j].rootId = v.id;
    }

    // Any group that is not cyclic.
    int headGroup = -1;
    for (int j=0; j<numGroups; ++j)
    {
        if (groups[j].cyclic == false)
        {
            headGroup = j;
            break;
        }
    }

#if TEST
    cout << "headGroup: " << headGroup << endl;
#endif

    // - If headGroup exists, Reparent the roots of other groups so that they point the headGroup's root.
    //   That requires (numGroups - 1) operations.
    // - If it does not exist, we need to convert one group as a headGroup, which requires one more operation.
    int numFixes = (headGroup == -1) ? numGroups : (numGroups - 1);

    // If not exist, convert a group as the head group.
    if (headGroup == -1)
    {
        Vertex& v = vertices[groups[0].anyMemberIndex];
        v.parentId = v.id;
        groups[0].rootId = v.id;
        groups[0].cyclic = false;
        headGroup = 0;
    }
    int headGroupRootId = groups[headGroup].rootId;

    // Let the roots of other groups to point to the root of the head group.
    for (int j=0; j<numGroups; ++j)
    {
        if (j != headGroup)
        {
            Group& G = groups[j];
            if (G.cyclic)
            {
                vertices[G.anyMemberIndex].parentId = headGroupRootId;
            }
            else
            {
                vertices[G.rootId - 1].parentId = headGroupRootId;
            }
        }
    }

    // Print the solution.
    cout << numFixes << endl;
    for (int i=0; i<n; ++i)
    {
        cout << vertices[i].parentId << ' ';
    }
    cout << endl;

    return 0;
}

