#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#define MAX numeric_limits<long long>::max() - 1
using namespace std;
class Node
{
public:
    int id;
    long long dist_from_src;
    static int cnt;
    vector< pair<Node*,long long> > neightbor;
    Node()
    {
        dist_from_src = MAX;
        id = ++cnt;
    }
};
int Node::cnt = 0;
struct Compare
{
    bool operator()(Node* A,Node* B)
    {
        return A->dist_from_src < B->dist_from_src;
    }
};
class Graph
{
private:

    int _size;
    Node* _nodes;
public:
    Graph(int n)
    {
        _size = n;
        Node::cnt = 0;
        _nodes = new Node[n];
    }
    long long dijsktra(int src,int target)
    {
        priority_queue<Node*,vector<Node*>,Compare> pq;
        _nodes[src].dist_from_src = 0;
        pq.push(&_nodes[src]);
        while(!pq.empty())
        {
            Node* parent = pq.top();
            pq.pop();
            for(int i = 0; i < parent->neightbor.size(); ++i)
            {
                if(parent->neightbor[i].first->dist_from_src > parent->dist_from_src + parent->neightbor[i].second)
                {
                    parent->neightbor[i].first->dist_from_src = parent->dist_from_src + parent->neightbor[i].second;
                    pq.push(parent->neightbor[i].first);
                }
            }
        }
        long long ans = _nodes[target].dist_from_src;
        for(int i = 0; i < _size; ++i)
        {
            _nodes[i].neightbor.clear();
            _nodes[i].dist_from_src = MAX;
        }
        return ans;
    }
   void connect(int A,int B,long long dist)
    {
        pair<Node*,long long> p1(&_nodes[B],dist);
        _nodes[A].neightbor.push_back(p1);
        pair<Node*,long long> p2(&_nodes[A],dist);
        _nodes[B].neightbor.push_back(p2);
    }
};
int main()
{

    int tc;
    cin >> tc;
    Graph g(50000);
    for(int i = 1; i <= tc; ++i)
    {
        int n,m,s,t;
        cin >> n >> m >> s >> t;
        for(int j = 0; j < m; ++j)
        {
            int a,b,dist;
            cin >> a >> b >> dist;
            g.connect(a,b,dist);
        }
        //g.display();
        long long ans = g.dijsktra(s,t);
        cout << "Case #" << i <<": ";
        if(ans == MAX)
        {
            cout << "unreachable" << endl;
        }
        else
        {
            cout << ans << endl;
        }
    }
    return 0;
}
