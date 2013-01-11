#pragma once
#include "StructureGraph.h"
#include "Dijkstra.h"

typedef std::map< int, std::pair<int,double> > CloseMap;

struct GraphDistanceNode{
	Vector3 pos;
	Structure::Node * n;
	int idx, gid;
	GraphDistanceNode(Vector3 & position, Structure::Node * node, int index, int globalID):
		pos(position),n(node),idx(index),gid(globalID){}
};

class GraphDistance
{
public:
    GraphDistance(Structure::Graph * graph, QVector<QString> exclude_nodes = QVector<QString>());
	GraphDistance(Structure::Node * n);

	int globalID;

	void prepareNodes( Scalar resolution, const std::vector<Vector3> & startingPoints, 
		CloseMap & closestStart, QVector<Structure::Node *> nodes );

	void computeDistances( Vector3 startingPoint, double resolution = -1 );
	void computeDistances( std::vector<Vector3> startingPoints, double resolution = -1 );

	double distance( Vector3 point );
    double pathTo( Vector3 point, std::vector<Vector3> & path );
	double pathCoordTo( Vector3 point, QVector< QPair<QString, Vec4d> > & path );
	Structure::Node * closestNeighbourNode( Vector3 to, double resolution = 0.25 );
	void clear();

	Structure::Graph * g;

	adjacency_list_t adjacency_list;
	std::vector<weight_t> min_distance;
	std::vector<vertex_t> previous;

	std::map< Structure::Node *, std::vector<GraphDistanceNode> > nodesMap;
	std::map< Structure::Node *, std::vector<Vector3> > samplePoints;
	std::map< Structure::Node *, std::pair<int,int> > nodeCount;

	std::vector<Vector3> allPoints;
	QVector< QPair<QString,Vec4d> > allCoords;
	std::vector<double> dists;
	std::vector<Structure::Node *> correspond;
	std::set< std::pair<int,int> > jumpPoints;
	QVector<QString> excludeNodes;

	bool isReady;

	// DEBUG:
	void draw();
};

static inline QVector<QString> SingleNode(const QString & nodeID){
	return QVector<QString>(1, nodeID);
}