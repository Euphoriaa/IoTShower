namespace VoiceRec
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button1 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.TestConnection = new System.Windows.Forms.Button();
            this.ArduinoEcho = new System.Windows.Forms.TextBox();
            this.commands = new System.Windows.Forms.RichTextBox();
            this.sendToArduino = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.TempLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(228, 491);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(292, 106);
            this.button1.TabIndex = 0;
            this.button1.Text = "Start Listening";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(228, 44);
            this.checkBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(144, 29);
            this.checkBox1.TabIndex = 1;
            this.checkBox1.Text = "connected";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // TestConnection
            // 
            this.TestConnection.ForeColor = System.Drawing.Color.DarkBlue;
            this.TestConnection.Location = new System.Drawing.Point(228, 130);
            this.TestConnection.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TestConnection.Name = "TestConnection";
            this.TestConnection.Size = new System.Drawing.Size(260, 36);
            this.TestConnection.TabIndex = 2;
            this.TestConnection.Text = "Test Connection";
            this.TestConnection.UseVisualStyleBackColor = true;
            this.TestConnection.Click += new System.EventHandler(this.TestConnection_Click);
            // 
            // ArduinoEcho
            // 
            this.ArduinoEcho.Location = new System.Drawing.Point(222, 86);
            this.ArduinoEcho.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ArduinoEcho.Name = "ArduinoEcho";
            this.ArduinoEcho.Size = new System.Drawing.Size(295, 31);
            this.ArduinoEcho.TabIndex = 3;
            this.ArduinoEcho.Text = "Arduino Echo";
            // 
            // commands
            // 
            this.commands.Location = new System.Drawing.Point(220, 175);
            this.commands.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.commands.Name = "commands";
            this.commands.Size = new System.Drawing.Size(296, 248);
            this.commands.TabIndex = 5;
            this.commands.Text = "here you see the voice recognession results, the arduino get its Serial input thr" +
    "ough this textbox also.";
            // 
            // sendToArduino
            // 
            this.sendToArduino.Location = new System.Drawing.Point(260, 434);
            this.sendToArduino.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.sendToArduino.Name = "sendToArduino";
            this.sendToArduino.Size = new System.Drawing.Size(228, 48);
            this.sendToArduino.TabIndex = 6;
            this.sendToArduino.Text = "send input to arduino";
            this.sendToArduino.UseVisualStyleBackColor = true;
            this.sendToArduino.Click += new System.EventHandler(this.sendToArduino_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(582, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(140, 25);
            this.label1.TabIndex = 7;
            this.label1.Text = "Temperature:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // TempLabel
            // 
            this.TempLabel.AutoSize = true;
            this.TempLabel.Location = new System.Drawing.Point(587, 91);
            this.TempLabel.Name = "TempLabel";
            this.TempLabel.Size = new System.Drawing.Size(0, 25);
            this.TempLabel.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.MenuHighlight;
            this.ClientSize = new System.Drawing.Size(771, 600);
            this.Controls.Add(this.TempLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.sendToArduino);
            this.Controls.Add(this.commands);
            this.Controls.Add(this.ArduinoEcho);
            this.Controls.Add(this.TestConnection);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Button TestConnection;
        private System.Windows.Forms.TextBox ArduinoEcho;
        private System.Windows.Forms.RichTextBox commands;
        private System.Windows.Forms.Button sendToArduino;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label TempLabel;
    }
}

