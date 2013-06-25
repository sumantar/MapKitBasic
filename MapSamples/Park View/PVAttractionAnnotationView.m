//
//  PVAttractionAnnotationView.m
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import "PVAttractionAnnotationView.h"
#import "PVAttractionAnnotation.h"

@implementation PVAttractionAnnotationView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (id)initWithAnnotation:(id<MKAnnotation>)annotation reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithAnnotation:annotation reuseIdentifier:reuseIdentifier];
    if (self) {
        PVAttractionAnnotation *attractionAnnotation = self.annotation;
        switch (attractionAnnotation.type) {
            case PVAttractionFirstAid:
                self.image = [UIImage imageNamed:@"firstaid"];
                break;
            case PVAttractionFood:
                self.image = [UIImage imageNamed:@"food"];
                break;
            case PVAttractionRide:
                self.image = [UIImage imageNamed:@"ride"];
                break;
            default:
                self.image = [UIImage imageNamed:@"star"];
                break;
        }
    }
    
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/


@end
