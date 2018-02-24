//
//  CMPageCollectionView.swift
//  iCampus_Swift
//
//  Created by wn on 2018/2/24.
//  Copyright © 2018年 wn. All rights reserved.
//

import UIKit

class CMPageCollectionView: UICollectionView {

}
extension CMPageCollectionView {
    class func createOnView(view:UIView,layout:UICollectionViewLayout,height:CGFloat,delegate:UICollectionViewDelegate,dataSource:UICollectionViewDataSource) -> CMPageCollectionView {
        let collection = Init(value: CMPageCollectionView(frame: CGRect.zero, collectionViewLayout: layout)) {
            $0.delegate =  delegate
            $0.dataSource = dataSource
            $0.translatesAutoresizingMaskIntoConstraints = false
            $0.decelerationRate = UIScrollViewDecelerationRateFast
            $0.showsHorizontalScrollIndicator = false
            $0.backgroundColor = UIColor(white: 0, alpha: 0)
        }
        view.addSubview(collection)
        
        // 增加constraints
        collection >>>- {
            $0.attribute = .height
            $0.constant = height
            return
        }
        [NSLayoutAttribute.left,.right,.centerY].forEach { (attribute) in
            (view, collection) >>>- {
                $0.attribute = attribute
                return
            }
        }
        
        return collection
    }
}
