MapKitBasic
===========

Ref: http://www.raywenderlich.com/30001/overlay-images-and-overlay-views-with-mapkit-tutorial

Controller needs to confirm delegate - MKMapViewDelegate. We used instancetype over id for LLVM compiler. (http://nshipster.com/instancetype/)

Step-1(Basic Setup)
===================
Lets theme park to be defined by coordinate and lets read a plist file for this purpose. In our project, lets create a model class - PVPark. This class will read the plist file and populate the following - CLLocationCoordinate2D (top-left, top-right, top-bottom coordinate). An array of boundary points - CLLocationCoordinate2D * (array). This is a C-structure and we need malloc to provide memory

Also provide a property as MKMapReck in this model class. Calculate boundary. MKMapPoint from MKMapPointsFromCoordinate which takes input as CLLocationCoordinate2D for each corner. Finally return as MKMapRectMake.

Now in controller side of story. Initialise the model and and set the span and region of the map. For calculating span, we will find the delta of latitude.

CLLocationDegrees latDelta = self.park.overlayTopLeftCoordinate.latitude - self.park.overlayBottomRightCoordinate.latitude;
MKCoordinateSpan span = MKCoordinateSpanMake(fabsf(latDelta), 0.0);
MKCoordinateRegion region = MKCoordinateRegionMake(self.park.midCoordinate, span);
self.mapView.region = region; 

For selecting different segment, we can set the map type: self.mapView.mapType = MKMapTypeStandard OR MKMapTypeHybrid OR MKMapTypeSatellite

Now we will see the map and zoomed to particular span and region, but not clear. We can select different map views like satellite/hybrid etc

Step-2 (Overlay)
=================
We need to show the overlay view. There are two concept behind it
1) MKOverlay: Instructs map view to draw overlay
	=> You need to define a class that confirms to protocol, MKOverlay. Look for this protocol design. It has properties.
	=> Need to define two properties, coordinate and boundingMapRect.
	Just need to synthesise the property. Need not to define it as it is defined in protocol.
	=> Finally we need to add this overlay to mapView
	
	We can initialise this class from our park model, where we have defined mid-coordinate and boundary

2) MKOverlayView: This view is defined internally by MapKit. We need to return this object from a delegate method, when overlay is added to the mapView.
	- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id<MKOverlay>)overlay
=> We can define our own class, derived from MKOverLayView and in drawRect, we can set the image
	- (void)drawMapRect:(MKMapRect)mapRect zoomScale:(MKZoomScale)zoomScale inContext:(CGContextRef)context {
    CGImageRef imageReference = self.overlayImage.CGImage;
 
    MKMapRect theMapRect = self.overlay.boundingMapRect;
    CGRect theRect = [self rectForMapRect:theMapRect];
 
    CGContextScaleCTM(context, 1.0, -1.0);
    CGContextTranslateCTM(context, 0.0, -theRect.size.height);
    CGContextDrawImage(context, theRect, imageReference);
}

---> Modify the controller to support these changes.

Step-3 (Annotation)
===================
As similar to the above class, we have two concept
1) MKAnnotation: 
	=> You need to define a class that confirms to protocol, MKAnnotation. Look for this protocol design. It has properties. coordinate, title, sub-title and also define our own custom type (may be reference to structure or enum). 
	=> Finally, add the annotation to the mapView

2) MKAnnotationView. We need to define a class to be derived from it. It has also image property where we can set it. We need to use the initialisation method, 
- (id)initWithAnnotation:(id<MKAnnotation>)annotation reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithAnnotation:annotation reuseIdentifier:reuseIdentifier];
    if (self) {
        PVAttractionAnnotation *attractionAnnotation = self.annotation;
	
	Based on annotation type, we can set the image
	
	=> Controller class, we need to read plist file (for this project) and crate each annotation and add those to map

	=> When we add annotation to map, it will have a callback method:
	- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation {
    		PVAttractionAnnotationView *annotationView = [[PVAttractionAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"Attraction"];
    		annotationView.canShowCallout = YES;
    		return annotationView;
	}
	
	=> We can customise the right button when callout is shown. Add the following line in the above delegate method:
	annotationView.rightCalloutAccessoryView = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
	=> When user taps, accessory view, the following delegate method will be invoked:
	- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl 			*)control
		{
    		NSLog(@"Callout accessory view is selected");
    		NSLog(@"accessory button tapped for annotation %@", view.annotation);
		}

	=> When annotation is tapped, the following delegate method will be invoked:
	- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view
		{
     		NSLog(@"Callout is tapped");
		}

Step-4 - Draw Directly on map view (MKPolyline)
===============================================
	=> Create an object of MKPolyline
	MKPolyline *myPolyline = [MKPolyline polylineWithCoordinates:pointsToUse count:pointsCount];
		Where, pointsToUse = array of type, CLLocationCoordinate2D and pointsCount = total number of points

	=> Add this object as overlay to the mapView
	[self.mapView addOverlay:myPolyline];

	=> Modify the callback delegate method:
	- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id<MKOverlay>)overlay {
   	 if ([overlay isKindOfClass:PVParkMapOverlay.class]) {
        		UIImage *magicMountainImage = [UIImage imageNamed:@"overlay_park"];
        		PVParkMapOverlayView *overlayView = [[PVParkMapOverlayView alloc] initWithOverlay:overlay overlayImage:magicMountainImage];
 
        		return overlayView;
    	} else if ([overlay isKindOfClass:MKPolyline.class]) {
        		MKPolylineView *lineView = [[MKPolylineView alloc] initWithOverlay:overlay];
        		lineView.strokeColor = [UIColor greenColor];
 
        		return lineView;
    	}
 
    	return nil;
	}

Note: We need to set the points, where map kit will draw the line

If we don't want in-app map, then use the following lines of code:
	MKPlacemark *placeMark = [[MKPlacemark alloc] initWithPlacemark:[placemarks objectAtIndex:0]];
    
    	MKMapItem *mapItem = [[MKMapItem alloc]initWithPlacemark:placeMark];
    
    	MKMapItem *mapItem2 = [MKMapItem mapItemForCurrentLocation];
    
    
    	NSArray *mapItems = @[mapItem, mapItem2];
    
    	NSDictionary *options = @{
                              MKLaunchOptionsDirectionsModeKey:MKLaunchOptionsDirectionsModeDriving,
                              MKLaunchOptionsMapTypeKey:
                                  [NSNumber numberWithInteger:MKMapTypeStandard],
                              MKLaunchOptionsShowsTrafficKey:@YES
                              };
    
    	[MKMapItem openMapsWithItems:mapItems launchOptions:options];



Step-4(A) - Showing the route from current location to tapped annotation 
========================================================================
It will launch the inbuilt map application and send the direction and route etc
=> Add the following code with your annotation class - PVAttractionAnnotation

- (MKMapItem*)mapItem;

- (MKMapItem*)mapItem {
    NSDictionary *addressDict = @{(NSString*)kABPersonAddressStreetKey : _subtitle};
    
    MKPlacemark *placemark = [[MKPlacemark alloc]
                              initWithCoordinate:self.coordinate
                              addressDictionary:addressDict];
    
    MKMapItem *mapItem = [[MKMapItem alloc] initWithPlacemark:placemark];
    mapItem.name = self.title;
    
    return mapItem;
}

=> Add the code when accessory view of callout is tapped:
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control
{
    NSLog(@"Callout accessory view is selected");
    NSLog(@"accessory button tapped for annotation %@", view.annotation);
    PVAttractionAnnotation *annotation = (PVAttractionAnnotation *)view.annotation;
    
    NSDictionary *launchOptions = @{MKLaunchOptionsDirectionsModeKey : MKLaunchOptionsDirectionsModeDriving};
    [annotation.mapItem openInMapsWithLaunchOptions:launchOptions];
}

Note: Since we are using: kABPersonAddressStreetKey. We need to add address book framework to it.



Step-5 - Draw Directly on map view (MKPolygon)
==============================================
	=> Create an object of MKPolyline
	 MKPolygon *polygon = [MKPolygon polygonWithCoordinates:self.park.boundary
                                                     count:self.park.boundaryPointsCount];
   	 [self.mapView addOverlay:polygon];

	=> Implement delegate method:
	- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id<MKOverlay>)overlay {

	----
	----

	} else if ([overlay isKindOfClass:MKPolygon.class]) {
        	MKPolygonView *polygonView = [[MKPolygonView alloc] initWithOverlay:overlay];
        	polygonView.strokeColor = [UIColor magentaColor];
 
        	return polygonView;
    }
 
    return nil;
}


Step-5 - Draw Directly on map view (MKCircle)
=============================================
=> Create Circle Object
	MKCircle *circle = [[MKCircle circleWithCenterCoordinate:CLLocationCoordinate2DMake(batmanPoint.x, batmanPoint.y) radius:MAX(5, rand()%40)];
	
=> Implement delegate method:

- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id<MKOverlay>)overlay {

	----
	----

	} else if ([overlay isKindOfClass:PVCharacter.class]) {
        MKCircleView *circleView = [[MKCircleView alloc] initWithOverlay:overlay];
        circleView.strokeColor = [(PVCharacter *)overlay color]];
 
        return circleView;
    }
 
    return nil;
}

Note: If you want to add additional stuffs, then create a class and derive it from MKCircle class and confirm to delegate method MKAnnotation. Add your required stuffs as shown in this sample