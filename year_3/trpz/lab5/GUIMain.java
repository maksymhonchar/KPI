package com.maxdev;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class GUIMain {
    private MsgAnalyzer msgAnalyzer;
    private JFrame mainFrame;
    private JTextArea inputArea;
    private JCheckBox containsChBx;
    private JCheckBox linkChBx;
    private JLabel resultLabel;
    private JButton checkBtn;

    public GUIMain() {
        prepareGUI();
    }

    public static void main(String[] args) {
        GUIMain swingControlDemo = new GUIMain();
        swingControlDemo.showEventDemo();
    }

    private void prepareGUI() {
        mainFrame = new JFrame("ТРПЗ ЛР5 КП-51 Гончар Максим");
        mainFrame.setSize(400, 400);

        msgAnalyzer = new MsgAnalyzer();

        JLabel infoLabel = new JLabel("Предмет: ПЗ контролю дотримання правил спільноти");
        inputArea = new JTextArea("Введіть повідомлення", 50, 32);
        checkBtn = new JButton("Перевірка");
        containsChBx = new JCheckBox("Містить заборонене слово", false);
        linkChBx = new JCheckBox("Містить посилання", false);
        resultLabel = new JLabel("Результат перевірки");

        mainFrame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent) {
                System.exit(0);
            }
        });

        JPanel infoPanel = new JPanel();
        infoPanel.add(infoLabel);
        JPanel inputPanel = new JPanel();
        inputPanel.add(inputArea);
        JPanel checkBxPanel = new JPanel();
        checkBxPanel.add(containsChBx);
        checkBxPanel.add(linkChBx);
        JPanel resultPanel = new JPanel();
        resultPanel.add(resultLabel);
        JPanel mainBtnPanel = new JPanel();
        mainBtnPanel.add(checkBtn);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.add(infoPanel);
        mainPanel.add(inputPanel);
        mainPanel.add(checkBxPanel);
        mainPanel.add(resultPanel);
        mainPanel.add(mainBtnPanel);

        mainFrame.add(mainPanel);
    }

    private void showEventDemo() {
        checkBtn.setActionCommand("Submit");
        checkBtn.addActionListener(new ButtonClickListener());
        mainFrame.setVisible(true);
    }

    private class ButtonClickListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();

            if (command.equals("Submit")) {
                String inputAreaText = inputArea.getText();
                String resultString = "";
                if (containsChBx.isSelected()) {
                    resultString += msgAnalyzer.checkMessageContains(inputAreaText);
                    resultString += "<br/>";
                }
                if (linkChBx.isSelected()) {
                    resultString += msgAnalyzer.checkMessageLink(inputAreaText);
                    resultString += "<br/>";
                }
                if (containsChBx.isSelected() && linkChBx.isSelected()) {
                    String a = msgAnalyzer.checkMessageContains(inputAreaText);
                    String b = msgAnalyzer.checkMessageLink(inputAreaText);
                    resultString = String.format("<html><p>%s</p><p>%s</p></html>", a, b);
                }
                if (!containsChBx.isSelected() && !linkChBx.isSelected()) {
                    resultString = "Будь ласка, виберіть тип перевірки.";
                }

                System.out.println("[" + resultString + "]");

                resultLabel.setText(resultString);
            }
        }
    }
}
