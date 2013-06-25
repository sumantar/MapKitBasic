//
//  PVPark.h
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@interface PVPark : NSObject

@property (nonatomic, readonly) CLLocationCoordinate2D *boundary;
@property (nonatomic, readonly) NSInteger boundaryPointsCount;

@property (nonatomic, readonly) CLLocationCoordinate2D midCoordinate;
@property (nonatomic, readonly) CLLocationCoordinate2D overlayTopLeftCoordinate;
@property (nonatomic, readonly) CLLocationCoordinate2D overlayTopRightCoordinate;
@property (nonatomic, readonly) CLLocationCoordinate2D overlayBottomLeftCoordinate;
@property (nonatomic, readonly) CLLocationCoordinate2D overlayBottomRightCoordinate;

@property (nonatomic, readonly) MKMapRect overlayBoundingMapRect;

@property (nonatomic, strong) NSString *name;

- (instancetype)initWithFilename:(NSString *)filename;

@end
