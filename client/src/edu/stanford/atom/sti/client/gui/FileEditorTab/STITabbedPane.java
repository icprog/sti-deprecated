/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * STITabbedPane.java
 *
 * Created on Oct 10, 2009, 2:10:06 AM
 */

package edu.stanford.atom.sti.client.gui.FileEditorTab;

import java.awt.Component;
import javax.swing.Icon;
import javax.swing.JTabbedPane;
import javax.swing.JLabel;


/**
 *
 * @author Owner
 */
public class STITabbedPane extends JTabbedPane {

    /** Creates new form BeanForm */
    public STITabbedPane() {
        initComponents();
    }


    @Override
    public void setTitleAt(int index, String title) {
        Component titleComponent = getTabComponentAt(index);
        if (titleComponent != null) {
            ((JLabel) titleComponent).setText(title);
        }
    }
    
    @Override
    public String getTitleAt(int index) {
        Component titleComponent = getTabComponentAt(index);
        if (titleComponent == null) {
            return "";
        }
        else {
            return ((JLabel) titleComponent).getText();
        }
        
    }

    @Override
    public void addTab(String title, Icon icon, Component component, String tip) {
        super.addTab(title, icon, component, tip);
        addCustomTabComponent(title);
    }
    @Override
    public void addTab(String title, Icon icon, Component component) {
        super.addTab(title, icon, component);
        addCustomTabComponent(title);
    }
    @Override
    public void addTab(String title, Component component) {
        super.addTab(title, component);
        addCustomTabComponent(title);
    }

    private void addCustomTabComponent(String title) {
        setTabComponentAt(getTabCount() - 1, new JLabel(title));
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

}