//
//  VideoPlayerController.h
//
//  Created by YangXP on 15-11-25.
//  Copyright (c) 2015年 StarsChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>

//播放器状态
typedef enum {
    E_PLAY_STATUS_NONE=0,
    E_PLAY_STATUS_CONTENT_LOADING,  //1
    E_PLAY_STATUS_CONTENT_LOADED,   //2
    E_PLAY_STATUS_OPENING,          //3
    E_PLAY_STATUS_OPENED,           //4
    E_PLAY_STATUS_OPEN_FAILED,      //5
    E_PLAY_STATUS_PLAYING,          //6
    E_PLAY_STATUS_PAUSED,           //7
    E_PLAY_STATUS_END,              //8
    E_PLAY_STATUS_CONTENT_UNLOADING,//9
    E_PLAY_STATUS_CONTENT_UNLOADED,//10
    E_PLAY_STATUS_GET_VIDEO_FAIL
}ePlayStatus;

//播放器类型
typedef enum {
    E_PLAYER_TYPE_NONE=0,
    E_PLAYER_TYPE_AD_VIDEO,
    E_PLAYER_TYPE_AD_IMAGE,
    E_PLAYER_TYPE_VOD,
    E_PLAYER_TYPE_LIVE,
    E_PLAYER_TYPE_BROADCAST,
    E_PLAYER_TYPE_REVIEW,
    E_PLAYER_TYPE_TIMEMOVE
}ePlayerType;

//当播放器状态发生变化时,发送此通知
extern NSString *const PlayerStatusChangedNotification;

//播放进度发生变化时,发送此通知
extern NSString *const PlayerProgressNotification;

//播放器缓存状态发生改变时,发送
//param--status
extern NSString *const PlayerCachingNotification;

////////////////////////////////////////////////////////////////

@interface VideoPlayerController : UIViewController


//播放地址
@property(atomic, readonly, copy) NSString *url;

//播放器类型
@property(atomic, readonly) ePlayerType eCurType;

//当前状态
@property(atomic, readonly) ePlayStatus eCurStatus;

//***********************
//isCaching:
//无帧可播->YES
//YES && 缓存数据>=minBufferedDuation->NO

//minBufferedDuation:
//缓存开始后,数据超过该值后恢复播放.避免频繁卡顿

//maxBufferedDuation:
//解码缓存的上限,超过后则暂停解码
//该值设小可减少内存开销,但网络抖动时会出现卡顿

//minBufferedDuation与maxBufferedDuation有默认设置,一般不需要上层关心
//当收到MemoryWarning时,会改变二者的值

@property(atomic, readonly) BOOL isCaching;

@property(atomic, readwrite) CGFloat minBufferedDuation;

@property(atomic, readwrite) CGFloat maxBufferedDuation;
//***********************

//系统的音量大小
@property(atomic, readwrite) CGFloat fVolume;

//当前播放位置
@property(atomic, readwrite) CGFloat fCurrentPosition;

//总时长
@property(atomic, readonly) CGFloat fTotalDuration;

//静音
@property(atomic, readwrite) BOOL isMute;

//屏幕内容的宽高比
@property(atomic, readonly) CGFloat fDisplayRatio;

// 缩放模式   默认UIViewContentModeScaleAspectFit
@property(atomic, readwrite) UIViewContentMode contentMode;

//内容区域(默认全屏)
@property(atomic, readwrite) CGRect renderRect;

//播放区域截图
- (UIImage *)getSnapshot;

//是否正在播放
- (BOOL)isPlaying;

//是否已经暂停
- (BOOL)isPaused;

//是否是直播
- (BOOL)isAlive;

//加载内容
- (void)loadContent:(NSString *)url andContentType:(ePlayerType)ePlayerType;

//卸载内容
- (void)unloadContent;

//重新加载
- (void)reload;

//播放
- (BOOL)play;

//暂停
- (BOOL)pause;

@end
