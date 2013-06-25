//
//  PVParkMapOverlay.h
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import "PVPark.h"

//@class PVPark;

@interface PVParkMapOverlay : NSObject <MKOverlay>
- (instancetype)initWithPark:(PVPark *)park;

@end
