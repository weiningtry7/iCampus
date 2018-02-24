//
//  ConfigurationHelper.swift
//  iCampus_Swift
//
//  Created by wn on 2018/2/24.
//  Copyright © 2018年 wn. All rights reserved.
//

import Foundation

internal func Init<Type>(value:Type,block:(_ object:Type) -> Void) -> Type {
    block(value)
    return  value
}
