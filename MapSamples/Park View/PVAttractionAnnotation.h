//
//  PVAttractionAnnotation.h
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

typedef NS_ENUM(NSInteger, PVAttractionType) {
    PVAttractionDefault = 0,
    PVAttractionRide,
    PVAttractionFood,
    PVAttractionFirstAid
};


@interface PVAttractionAnnotation : NSObject <MKAnnotation>

@property (nonatomic) CLLocationCoordinate2D coordinate;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSString *subtitle;
@property (nonatomic) PVAttractionType type;

@end
