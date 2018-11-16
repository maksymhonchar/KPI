package com.maxdev;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.GeneralPath;

@SuppressWarnings("serial")
public class TVAnimation extends JPanel implements ActionListener {
    private static int maxWidth;
    private static int maxHeight;

    // the antenna coords
    double points[][] = {
            { -50, -80 }, { 50, -80 }, { 0, -25 },
    };

    Timer timer;

    // Для анімації масштабування
    private double scale = 1;
    private double delta = 0.01;

    // for movement animation
    private double tx = 1;
    private double ty = 0;
    private double deltaX = 1;
    private int radius = 200;
    private int radiusExtention = 110;

    public TVAnimation() {
        timer = new Timer(10, this);
        timer.start();
    }

    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;

         // Set rendering params.
         RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
         rh.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
         g2d.setRenderingHints(rh);

        // Set background color.
        g2d.setBackground(new Color(127, 254, 0));
        g2d.clearRect(0, 0, maxWidth, maxHeight);

        // Set (0;0) to the center to draw main Frame.
        g2d.translate(maxWidth/2, maxHeight/2);
        // Draw the main Frame.
        BasicStroke bs2 = new BasicStroke(16, BasicStroke.CAP_ROUND, BasicStroke.JOIN_MITER);
        g2d.setStroke(bs2);
        g2d.drawRect(
                -(radius + radiusExtention),
                -(radius + radiusExtention),
                (radius + radiusExtention)*2,
                (radius + radiusExtention)*2
        );

        // Reset center to default value for the main animation.
        g2d.translate(tx, ty);

        // Set antenna crazy_triangle
        GeneralPath antenna = new GeneralPath();
        antenna.moveTo(points[0][0], points[0][1]);
        for (int k = 1; k < points.length; k++)
            antenna.lineTo(points[k][0], points[k][1]);
        antenna.closePath();

        // Draw antenna.
        GradientPaint gp = new GradientPaint(
                25, 50,
                new Color(202, 0, 66),
                60, 5,
                new Color(252, 163, 205),
                true
        );
        g2d.setPaint(gp);
        g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, (float) scale));
        g2d.fill(antenna);

        // Draw TV body.
        g2d.setColor(new Color(254, 165, 0));
        g2d.fillRect(-90, -25, 180, 115);

        // Draw TV screen.
        g2d.setColor(new Color(127, 127, 127));
        g2d.fillRoundRect(-85, -20,125,105, 25, 25);

        // Draw three dots near the screen.
        g2d.setColor(new Color(0,0,0));
        g2d.fillRoundRect(70, 30, 10,10, 100, 100);

        g2d.setColor(new Color(0,0,0));
        g2d.fillRoundRect(70, 50, 10,10, 100, 100);

        g2d.setColor(new Color(0,0,0));
        g2d.fillRoundRect(70, 70, 10,10, 100, 100);
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Lab2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(750, 750);
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.add(new TVAnimation());

        frame.setVisible(true);

        Dimension size = frame.getSize();
        Insets insets = frame.getInsets();
        maxWidth = size.width - insets.left - insets.right - 1;
        maxHeight = size.height - insets.top - insets.bottom - 1;
    }

    public void actionPerformed(ActionEvent e) {
        // scaling
        if (scale < 0.01) {
            delta = -delta;
        } else if (scale > 0.99) {
            delta = -delta;
        }

        // movement
        double radiusInSquare = Math.pow(radius, 2);
        if (tx <= 0 && ty < 0){
            tx -= deltaX;
            ty = (-1) * Math.abs(Math.sqrt(radiusInSquare - Math.pow(tx, 2)));
        }else if(tx > 0 && ty <= 0){
            tx -= deltaX;
            ty = (-1) * Math.abs(Math.sqrt(radiusInSquare - Math.pow(tx, 2)));
        }else if(tx >= 0 && ty > 0){
            tx += deltaX;
            ty = Math.abs(Math.sqrt(radiusInSquare - Math.pow(tx, 2)));
        }else if(tx < 0 && ty >= 0){
            tx += deltaX;
            ty = Math.abs(Math.sqrt(radiusInSquare - Math.pow(tx, 2)));
        }

        scale += delta;

        repaint();
    }
}
