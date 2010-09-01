
#ifndef MODEST_MAP
#define MODEST_MAP

#include <set>
#include <map>

#include "AbstractMapProvider.h"
#include "Location.h"
#include "Coordinate.h"
#include "Point2d.h"
#include "QueueSorter.h"
#include "TileLoader.h"

#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;

#define TILE_SIZE 256.0

// limit tiles in memory
// 256 would be 64 MB, you may want to lower this quite a bit for your app
// (we'll always keep as many images as needed to fill the screen though)
#define MAX_IMAGES_TO_KEEP 256

// upping this can help appearances when zooming out, but also loads many more tiles
#define GRID_PADDING 1


class Map {
	
public:
	
	// pan and zoom
	Coordinate centerCoordinate;
	
	// what kinda maps?
	AbstractMapProvider* provider;
	
	// how big?
	double width, height;
	
	// loading tiles
	TileLoader tileLoader;

	// loaded tiles
	std::map<Coordinate, gl::Texture> images;
	
	// coords waiting to load
	std::vector<Coordinate> queue;
	
	// a list of the most recent MAX_IMAGES_TO_KEEP ofImages we've seen
	std::vector<gl::Texture> recentImages;
	
	// keep track of what we can see already:
	std::set<Coordinate> visibleKeys;

	// previous mouse position
	double px;
	double py;
	
	/////////////////////////// methods	
	
	Map() {}
	
	void setup(AbstractMapProvider* _provider, double _width, double _height);	
	void update();
	void draw();
		
	void panBy(double x, double y);
	void scaleBy(double s);
	void scaleBy(double s, double x, double y);
	
	int getZoom();	
	Location getCenter();
	Coordinate getCenterCoordinate();
	
	void setCenter(Coordinate center);
	
	void setCenter(Location location);
	
	void setCenterZoom(Location location, int zoom);
	
	void setZoom(double zoom);
	
	void zoomBy(double distance);
	
	void zoomIn();
	
	void zoomOut();
	
	// TODO: extent functions
	//	    public function setExtent(extent:MapExtent):void
	//	    public function getExtent():MapExtent
	
	// TODO: make it so you can safely get and set the provider
	/*AbstractMapProvider getMapProvider() {
	    return provider;
	}
	
	void setMapProvider(AbstractMapProvider _provider) {
		provider = _provider;
		images.clear();
		queue.clear();
		pending.clear();
	}*/
	
	Point2d coordinatePoint(Coordinate coord);
    
	Coordinate pointCoordinate(Point2d point);
	
	Point2d locationPoint(Location location);
	
	Location pointLocation(Point2d point);
	
	// TODO: pan by proportion of screen size, not by coordinate grid
	void panUp();
	void panDown();
	void panLeft();
	void panRight();
	
	void panAndZoomIn(Location location);
	
	void panTo(Location location);
	
	///////////////////////////////////////////////////////////////////////
	
	float scaleForZoom(int zoom);
	
	float zoomForScale(float scale);
	
	int bestZoomForScale(float scale);
	
	//////////////////////////////////////////////////////////////////////////
	
	
	void grabTile(Coordinate coord);
	
	void processQueue();
	
};

#endif
