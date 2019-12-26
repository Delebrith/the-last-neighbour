#pragma once
#include <vector>
#include <set>
#include "point.h"
#include "CreatedPoint.h"
#include "DatasetPoint.h"
#include "reference_strategy.h"

class NBCRunner 
{
protected:
	// set is sorted using greater operator, thus largest elements will be at the beginning
	typedef std::set<std::pair<double, Point*>, std::greater<std::pair<double, Point*>>> orderedNeighborhood;


	int k;
	CreatedPoint referencePoint;
	std::vector<DatasetPoint> points;

	std::vector<DatasetPoint> initPoints(const std::vector<std::vector<double>>& features);

	void calculateNeighborhoods(std::vector<Point*>& order);
	void calculatePointNeighborhood(int pointId, std::vector<Point*>& order);
	virtual void insertCloserPointToNeihborhood(orderedNeighborhood&, Point* point, double dist) = 0;
	void calculateReversedNeighbourhoods();
	void calculateNDFs();

	CreatedPoint selectReferencePoint(const std::vector<std::vector<double>>& features,
		const ReferenceStrategy referenceStrategy);
	std::vector<double>& getMaxValues(const std::vector<std::vector<double>>& features);
	std::vector<double>& getMinValues(const std::vector<std::vector<double>>& features);
	double calculateDistanceToReferencePoint(Point& point);

public:
	NBCRunner(int k, const ReferenceStrategy referenceStrategy, const std::vector<std::vector<double>>& features);
	std::vector<int> run();
};