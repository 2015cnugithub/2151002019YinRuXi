package sphere;

import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

public class GraphicsController implements MouseMotionListener{

	//该控制器所控制的Sphere对象
    private Sphere sphere;
    
    /** Creates a new instance of TextController */
    public GraphicsController(Sphere sphere) {
        this.sphere=sphere;
    }
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		if(e.getX()>0)
			sphere.setRadius(e.getX());
		else sphere.setRadius(0);
		
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

}
