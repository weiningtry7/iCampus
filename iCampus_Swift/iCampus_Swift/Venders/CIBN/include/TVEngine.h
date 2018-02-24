//
//  TVEngine.h
//  
//
//  Created by Zy on 15/12/5.
//  Copyright © 2015年 StarsChina. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "VideoPlayerController.h"
#import <CoreFoundation/CoreFoundation.h>


typedef NS_ENUM(NSInteger, TVELoadVideoType) {
    TVE_LOAD_VIDEO_TYPE_LIVE     = 1,     //直播
    TVE_LOAD_VIDEO_TYPE_REVIEW   = 2,     //回看
    TVE_LOAD_VIDEO_TYPE_TIMEMOVE = 3,     //时移
    TVE_LOAD_VIDEO_TYPE_VOD      = 4,     //点播
    TVE_LOAD_VIDEO_TYPE_LOCALTION= 5,     //本地
};

typedef enum{
    ADSTART,                        //广告开始
    ADEND,                          //广告结束
    ADERROR                         //广告展示失败
}AdvertimentType;

typedef enum {
    LOADING,
    LOADING_VIDEO,                   //前贴片
    LOADING_IMAGE,
    PREINSERT,                      //前插屏
    BANNER
}ADPosition;

@protocol ClearADProtocol <NSObject>

@optional
- (void)clearADAction;
@end


typedef void (^CreatSuccessBlock)(BOOL creatSuccess, NSError* error);
typedef void (^ListBlock)(NSArray *list, NSError *error);
typedef void (^EPGBlock)(NSArray *epgList, NSError *error);
typedef void (^CurrentBlock)(NSArray *curentList, NSError *error);
typedef void (^GetStartViewControllerBlock)(BOOL end);
typedef void (^AD_ExitBlock)(void);
typedef void (^GetBannerCompletion)(UIView *adView, NSError *error);
typedef void (^AdvertismentBlock)(AdvertimentType type,ADPosition position,UIView *advertismentView);


@interface TVEngine : NSObject

/**
 *  注册
 */
+ (void)creatWithSDKAppKey:(NSString *)appKey success:(CreatSuccessBlock)successBlock;

/**
 *  销毁
 */
+ (void)destroy;

/**
 *  是否已经注册
 */
+ (BOOL)isRegistered;

/**
 *  根据视频ID来播放视频 （点播和直播可用刺接口）
 *
 *  @param videoID 视频ID
 *  @param by      自定义的播放器
 *  @param type    TVELoadVideoType
 */
+ (void)loadVideoWithID:(NSString *)videoID By:(VideoPlayerController *)by andType:(TVELoadVideoType)type;

/**
 *  根据视频ID来播放视频 （时移回看可使用此接口）
 *
 *  @param videoID 视频ID
 *  @param by      自定义的播放器
 *  @param type    TVELoadVideoType
 *  @param startTime  开始的Unix时间戳
 */
+ (void)loadVideoWithID:(NSString *)videoID By:(VideoPlayerController *)by andType:(TVELoadVideoType)type startUnixTime:(NSInteger)startTime;

/**
 *  根据视频url来播放视频
 *
 *  @param url url
 */
+ (void)loadVideoWithUrl:(NSString *)url By:(VideoPlayerController *)by;

/**
 *  根据VideoId获取竖屏横幅广告
 *
 *  @param videoID      视频ID
 *  @param completion   完成回调
 */
+ (void)loadVideoBannerAdWithID:(NSString *)videoID completion:(GetBannerCompletion)completion;

/**
 *  结束
 */
+ (void)unLoadVideo;

/**
 *  获取频道列表
 *
 *  @param listBlock 频道列表的block
     @"videoId":                    频道id
     @"videoName":                  频道名称
     @"icon":                       频道图标
     @"currentImage":               频道截图
     @"area":                       频道地区
 */
+ (void)getChannelList:(ListBlock)listBlock;

/**
 *  取得相应频道的当日节目单信息（节目单会随着电视台的调整而与已获取到的节目单信息造成差异）
 *
 *  @param channelID 频道ID
 *  @param epgBlock  节目单
        @"title":                   节目名称
        @"timeInterval":            节目开始时间（时间戳since1970）
        @"endTimeInterval":         节目结束时间（时间戳since1970）
 */
+ (void)getEPGListWith:(NSString *)channelID block:(EPGBlock)epgBlock;


/**
 *  取得相应频道的前七天节目单信息（节目单会随着电视台的调整而与已获取到的节目单信息造成差异）
 *
 *  @param Date 日期（只支持前七天＋后两天）
 *  @param channelID 频道ID
 *  @param epgBlock  节目单
 @"title":                   节目名称
 @"timeInterval":            节目开始时间（时间戳since1970）
 @"endTimeInterval":         节目结束时间（时间戳since1970）
 */
+ (void)getEPGListWith:(NSString *)channelID withDate:(NSDate *)date block:(EPGBlock)epgBlock;

/**
 *  获取传入的频道数组正在播放以及下一个播放的节目的数组
 *
 *  @param channelID 频道id
 *  @param block     返回参数block
 
    @"current":         当前正在播放的节目字典
    @"next":            下一个要播放的节目字典
 
    节目字典属性:
        @"name":                    节目名
        @"timeInterval":            节目开始时间（时间戳since1970）
        @"endTimeInterval":         节目结束时间（时间戳since1970）
 */
+ (void)getCurrentPlayingChannleWith:(NSArray *)channelID block:(CurrentBlock)block;

/**
 *  设置语言
 *
 *  @param languge 语言种类：zh-Hans,zh-Hant,en
 */
+ (void)setLanguge:(NSString *)languge;

/**
 *  开机图控制器
 *
 *  @param block 结束回调的block
 *
 *  @return 开机图控制器
 */
+ (UIViewController *)getStartViewControllerAndBlock:(GetStartViewControllerBlock)block;

/**
 *  广告过程中退出所调用的block
 */
+ (void)setADExitBlock:(AD_ExitBlock)block;


/**
 *  广告相关
 *
 *  @param advertismentBlock
 */
+ (void)setAdvertismentBlock:(AdvertismentBlock)advertismentBlock;

/**
 *  广告按钮图片
 *
 *  @param timerImgPath  倒计时背景图
 *  @param clodeImgPath  关闭按钮图片
 *  @param detailImgPath 了解详情背景图
 */
+ (void)setAdvertismentButtonImageAboutTimerImgPath:(NSString*)timerImgPath
                                    andCloseImgPath:(NSString*)closeImgPath
                                   andDetailImgPath:(NSString*)detailImgPath;

/**
 *  获取Sdk版本号
 *  方便迭代时查找问题
 */
+ (NSString *)getTVEngineVersion;
@end
