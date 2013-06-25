//
//  PVParkMapOverlay.m
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import "PVParkMapOverlay.h"

@implementation PVParkMapOverlay

@synthesize coordinate;
@synthesize boundingMapRect;

- (instancetype)initWithPark:(PVPark *)park
{
    self = [super init];
    if (self) {
        boundingMapRect = park.overlayBoundingMapRect;
        coordinate = park.midCoordinate;
    }
    
    return self;
}
@end
