import Foundation
import UIKit

class CircleView : UIView {
    
       
    func move() -> Int {
        return Int.random(in: 0...500)
       }
    
    func changeSize() -> Int {
        return Int.random(in: 5...300)
    }

    override func draw(_ rect: CGRect) {

        let background = UIBezierPath(rect: bounds)
        UIColor.black.setFill()
        background.fill()


        let X = move()
        let Y = move()
        let size = changeSize()
        let  rect = CGRect(x: X, y: Y, width: size, height: size)
        let circle = UIBezierPath(ovalIn: rect)


        //        I adopted this Color randomizer from Github but all the rest of it was me. I          just wanted to add color to the animation.
        let hue : CGFloat = CGFloat(arc4random() % 256) / 256
        let saturation : CGFloat = CGFloat(arc4random() % 128) / 256 + 0.5
        let brightness : CGFloat = CGFloat(arc4random() % 128) / 256 + 0.5

        UIColor(hue: hue, saturation: saturation, brightness: brightness, alpha: 1).setFill()


        circle.fill()

        DispatchQueue.main.asyncAfter(deadline: .now() + 1.5 / 6.0){
                    self.setNeedsDisplay()
                }
    }
 
}
