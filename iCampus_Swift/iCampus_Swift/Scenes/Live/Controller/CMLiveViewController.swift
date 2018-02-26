//
//  CMLiveViewController.swift
//  iCampus_Swift
//
//  Created by wn on 2018/2/24.
//  Copyright © 2018年 wn. All rights reserved.
//

import UIKit

class CMLiveViewController: CMBaseController {
    var dataSource: [LiveListModel] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        if TVEngine.isRegistered() {
            TVEngine.getChannelList { (array, _) in
                print(array ?? [])
            }
        } else {
            TVEngine.creat(withSDKAppKey: "MDgxY2I2MGRhZGUw") { (success, error) in
                if success {
                    TVEngine.getChannelList { (array, _) in
                        guard let data = array else { return  }
                        self.dataSource = [LiveListModel].deserialize(from: data)! as! [LiveListModel]
                        print(self.dataSource[0])
                        }
                } else {
                    print("failure")
                }
            }
        }
       
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
