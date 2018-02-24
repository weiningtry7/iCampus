//
//  CMPageCollectionLayout.swift
//  iCampus_Swift
//
//  Created by wn on 2018/2/24.
//  Copyright © 2018年 wn. All rights reserved.
//

import UIKit

class CMPageCollectionLayout: UICollectionViewFlowLayout {
    fileprivate var lastCollectionViewSize:CGSize = CGSize.zero
    var scalingOffset: CGFloat = 200
    var minimumScaleFactor: CGFloat = 0.9
    var minimumAlphaFactor: CGFloat = 0.3
    var scaleItems: Bool = true
    
    required init?(coder aDecoder: NSCoder) {
        fatalError()
    }
    init(itemSize:CGSize) {
        super.init()
        commonInit(itemSize)
        
    }
}
// MARK: --初始化
extension CMPageCollectionLayout {
    
    func commonInit(_ itemSize:CGSize) {
        self.scrollDirection = .horizontal
        self.minimumLineSpacing = 25
        self.itemSize = itemSize
    }
    
}
// MARK: --重写
extension CMPageCollectionLayout {
    override func invalidateLayout(with context: UICollectionViewLayoutInvalidationContext) {
        super.invalidateLayout(with: context)
        guard let collectionView = self.collectionView else {
            return
        }
        if collectionView.bounds.size != lastCollectionViewSize {
            configureInset()
            lastCollectionViewSize = collectionView.bounds.size
        }
    }
    // 滑动改变cell的位置
    override func targetContentOffset(forProposedContentOffset proposedContentOffset: CGPoint, withScrollingVelocity velocity: CGPoint) -> CGPoint {
        guard let collectionView = self.collectionView else {
            return proposedContentOffset
        }
        let proposeRect = CGRect(x: proposedContentOffset.x, y: 0, width: collectionView.bounds.size.width, height: collectionView.bounds.size.height)
        guard let layoutAttributes = self.layoutAttributesForElements(in: proposeRect) else {
            return proposedContentOffset
        }
        
        let proposeContentOffsetCenterX = proposedContentOffset.x + collectionView.bounds.size.width/2
        var candidateAttributes: UICollectionViewLayoutAttributes?
        
        for attributes in layoutAttributes {
            if attributes.representedElementCategory != .cell {
                continue
            }
            if candidateAttributes == nil {
                candidateAttributes = attributes
                continue
            }
            if fabs(attributes.center.x - proposeContentOffsetCenterX) < fabs(candidateAttributes!.center.x - proposeContentOffsetCenterX){
                candidateAttributes = attributes
            }
            
        }
        guard let aCandidateAttributes = candidateAttributes else {
            return proposedContentOffset
        }
        var newOffsetX = aCandidateAttributes.center.x - collectionView.bounds.size.width/2
        let offset = newOffsetX - collectionView.contentOffset.x
        
        if (velocity.x < 0 && offset > 0) || (velocity.x > 0 && offset < 0) {
            let pageWidth = itemSize.width + minimumLineSpacing
            newOffsetX += velocity.x > 0 ? pageWidth: -pageWidth
            
        }
        
        return CGPoint(x:newOffsetX, y:proposedContentOffset.y)
    }
    
    override func shouldInvalidateLayout(forBoundsChange newBounds: CGRect) -> Bool {
        return true
    }
    // 设置cell的透明度,缩放比例
    override func layoutAttributesForElements(in rect: CGRect) -> [UICollectionViewLayoutAttributes]? {
        guard let collectionView = self.collectionView,
             let superAttributes = super.layoutAttributesForElements(in: rect) else {
    
                return super.layoutAttributesForElements(in: rect)
        }
        if scaleItems == false {
            return super.layoutAttributesForElements(in: rect)
        }
        // 偏移量
        let contentOffset = collectionView.contentOffset
        // size
        let size = collectionView.bounds.size
        // 可视区域的Rect
        let visiableRect = CGRect(x: contentOffset.x, y: contentOffset.y, width: size.width, height: size.height)
        let visibleCenterX = visiableRect.midX
        // 遍历属性,缩放,透明度
        guard case let newAttributesArray as [UICollectionViewLayoutAttributes]  = NSArray(array:superAttributes, copyItems:true) else {
            return nil
        }
        newAttributesArray.forEach {
            let distanceFromCenter = visibleCenterX - $0.center.x
            let absDistanceFromCenter = min(abs(distanceFromCenter), self.scalingOffset)
            let scale = absDistanceFromCenter * (self.minimumScaleFactor - 1) / self.scalingOffset + 1
            $0.transform3D = CATransform3DScale(CATransform3DIdentity, scale, scale, 1)
            
            let alpha = absDistanceFromCenter * (self.minimumAlphaFactor - 1) / self.scalingOffset + 1
            $0.alpha = alpha
    
        }
        return newAttributesArray
    }
    
}
// MARK: --helpers
extension CMPageCollectionLayout {
    
    func configureInset() {
        guard let collection = self.collectionView else {
            return
        }
        let insert = collection.bounds.size.width/2 - itemSize.width/2
        collection.contentInset = UIEdgeInsetsMake(0, insert, 0, insert)
        collection.contentOffset = CGPoint(x: -insert, y: 0)
        
    }
}

