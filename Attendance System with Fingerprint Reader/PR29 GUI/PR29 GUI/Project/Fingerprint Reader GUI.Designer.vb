<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.txtReceive = New System.Windows.Forms.TextBox
        Me.cmdReceive = New System.Windows.Forms.Button
        Me.SerialPort = New System.IO.Ports.SerialPort(Me.components)
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.FileContents = New System.Windows.Forms.TextBox
        Me.cboUser = New System.Windows.Forms.ComboBox
        Me.StatusStrip1 = New System.Windows.Forms.StatusStrip
        Me.StatusPanel = New System.Windows.Forms.ToolStripStatusLabel
        Me.cmdTest = New System.Windows.Forms.Button
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog
        Me.FileName = New System.Windows.Forms.Label
        Me.OpenFile = New System.Windows.Forms.Button
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog
        Me.SaveTo = New System.Windows.Forms.Button
        Me.txtStatus = New System.Windows.Forms.TextBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.cmdPortClose = New System.Windows.Forms.Button
        Me.cmdPortOpen = New System.Windows.Forms.Button
        Me.radioPR29 = New System.Windows.Forms.RadioButton
        Me.cboBaudRate = New System.Windows.Forms.ComboBox
        Me.radioReader = New System.Windows.Forms.RadioButton
        Me.cboPort = New System.Windows.Forms.ComboBox
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.cmdGetTotal = New System.Windows.Forms.Button
        Me.cmdAdd = New System.Windows.Forms.Button
        Me.cmdDelete = New System.Windows.Forms.Button
        Me.GroupBox3 = New System.Windows.Forms.GroupBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.StatusStrip1.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.SuspendLayout()
        '
        'txtReceive
        '
        Me.txtReceive.Enabled = False
        Me.txtReceive.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtReceive.Location = New System.Drawing.Point(24, 384)
        Me.txtReceive.Multiline = True
        Me.txtReceive.Name = "txtReceive"
        Me.txtReceive.Size = New System.Drawing.Size(214, 10)
        Me.txtReceive.TabIndex = 5
        Me.ToolTip1.SetToolTip(Me.txtReceive, "Data received")
        Me.txtReceive.Visible = False
        '
        'cmdReceive
        '
        Me.cmdReceive.Enabled = False
        Me.cmdReceive.Location = New System.Drawing.Point(252, 406)
        Me.cmdReceive.Name = "cmdReceive"
        Me.cmdReceive.Size = New System.Drawing.Size(102, 23)
        Me.cmdReceive.TabIndex = 7
        Me.cmdReceive.Text = "Get Attendance"
        Me.cmdReceive.UseVisualStyleBackColor = True
        '
        'SerialPort
        '
        Me.SerialPort.BaudRate = 19200
        '
        'FileContents
        '
        Me.FileContents.Location = New System.Drawing.Point(256, 204)
        Me.FileContents.Multiline = True
        Me.FileContents.Name = "FileContents"
        Me.FileContents.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.FileContents.Size = New System.Drawing.Size(191, 189)
        Me.FileContents.TabIndex = 14
        Me.ToolTip1.SetToolTip(Me.FileContents, "Attendance from PR29")
        '
        'cboUser
        '
        Me.cboUser.Enabled = False
        Me.cboUser.FormattingEnabled = True
        Me.cboUser.Items.AddRange(New Object() {"User 1", "User 2", "User 3", "User 4", "User 5"})
        Me.cboUser.Location = New System.Drawing.Point(7, 20)
        Me.cboUser.Name = "cboUser"
        Me.cboUser.Size = New System.Drawing.Size(215, 21)
        Me.cboUser.TabIndex = 23
        Me.cboUser.Text = "Choose User..."
        Me.ToolTip1.SetToolTip(Me.cboUser, "Select which user to delete/add")
        '
        'StatusStrip1
        '
        Me.StatusStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.StatusPanel})
        Me.StatusStrip1.Location = New System.Drawing.Point(0, 511)
        Me.StatusStrip1.Name = "StatusStrip1"
        Me.StatusStrip1.Size = New System.Drawing.Size(465, 22)
        Me.StatusStrip1.TabIndex = 10
        Me.StatusStrip1.Text = "StatusStrip1"
        '
        'StatusPanel
        '
        Me.StatusPanel.Name = "StatusPanel"
        Me.StatusPanel.Size = New System.Drawing.Size(450, 17)
        Me.StatusPanel.Spring = True
        Me.StatusPanel.Text = "ToolStripStatusLabel1"
        '
        'cmdTest
        '
        Me.cmdTest.Location = New System.Drawing.Point(6, 110)
        Me.cmdTest.Name = "cmdTest"
        Me.cmdTest.Size = New System.Drawing.Size(92, 38)
        Me.cmdTest.TabIndex = 11
        Me.cmdTest.Text = "Matching" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "( 1 : N )"
        Me.cmdTest.UseVisualStyleBackColor = True
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'FileName
        '
        Me.FileName.BackColor = System.Drawing.SystemColors.ActiveCaption
        Me.FileName.Location = New System.Drawing.Point(53, 179)
        Me.FileName.Name = "FileName"
        Me.FileName.Size = New System.Drawing.Size(191, 23)
        Me.FileName.TabIndex = 13
        Me.FileName.Visible = False
        '
        'OpenFile
        '
        Me.OpenFile.Location = New System.Drawing.Point(22, 406)
        Me.OpenFile.Name = "OpenFile"
        Me.OpenFile.Size = New System.Drawing.Size(75, 23)
        Me.OpenFile.TabIndex = 15
        Me.OpenFile.Text = "Open a File"
        Me.OpenFile.UseVisualStyleBackColor = True
        Me.OpenFile.Visible = False
        '
        'SaveTo
        '
        Me.SaveTo.Location = New System.Drawing.Point(368, 406)
        Me.SaveTo.Name = "SaveTo"
        Me.SaveTo.Size = New System.Drawing.Size(75, 23)
        Me.SaveTo.TabIndex = 16
        Me.SaveTo.Text = "Save As..."
        Me.SaveTo.UseVisualStyleBackColor = True
        '
        'txtStatus
        '
        Me.txtStatus.BackColor = System.Drawing.SystemColors.ActiveCaption
        Me.txtStatus.Font = New System.Drawing.Font("Microsoft Sans Serif", 20.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtStatus.ForeColor = System.Drawing.Color.DeepPink
        Me.txtStatus.Location = New System.Drawing.Point(22, 452)
        Me.txtStatus.Name = "txtStatus"
        Me.txtStatus.Size = New System.Drawing.Size(425, 38)
        Me.txtStatus.TabIndex = 18
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(20, 75)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(58, 13)
        Me.Label2.TabIndex = 9
        Me.Label2.Text = "Baud Rate"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(20, 28)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(101, 13)
        Me.Label1.TabIndex = 8
        Me.Label1.Text = "Communication Port"
        '
        'cmdPortClose
        '
        Me.cmdPortClose.Enabled = False
        Me.cmdPortClose.Location = New System.Drawing.Point(230, 87)
        Me.cmdPortClose.Name = "cmdPortClose"
        Me.cmdPortClose.Size = New System.Drawing.Size(75, 23)
        Me.cmdPortClose.TabIndex = 3
        Me.cmdPortClose.Text = "Close"
        Me.cmdPortClose.UseVisualStyleBackColor = True
        '
        'cmdPortOpen
        '
        Me.cmdPortOpen.Location = New System.Drawing.Point(230, 47)
        Me.cmdPortOpen.Name = "cmdPortOpen"
        Me.cmdPortOpen.Size = New System.Drawing.Size(75, 23)
        Me.cmdPortOpen.TabIndex = 2
        Me.cmdPortOpen.Text = "Open"
        Me.cmdPortOpen.UseVisualStyleBackColor = True
        '
        'radioPR29
        '
        Me.radioPR29.AutoSize = True
        Me.radioPR29.Enabled = False
        Me.radioPR29.Location = New System.Drawing.Point(6, 19)
        Me.radioPR29.Name = "radioPR29"
        Me.radioPR29.Size = New System.Drawing.Size(119, 17)
        Me.radioPR29.TabIndex = 19
        Me.radioPR29.TabStop = True
        Me.radioPR29.Text = "Interface with PR29"
        Me.radioPR29.UseVisualStyleBackColor = True
        '
        'cboBaudRate
        '
        Me.cboBaudRate.FormattingEnabled = True
        Me.cboBaudRate.Items.AddRange(New Object() {"115200", "57600", "38400", "19200", "9600", "4800", "2400", "1200", "600", "300"})
        Me.cboBaudRate.Location = New System.Drawing.Point(20, 89)
        Me.cboBaudRate.Name = "cboBaudRate"
        Me.cboBaudRate.Size = New System.Drawing.Size(166, 21)
        Me.cboBaudRate.TabIndex = 1
        Me.cboBaudRate.Text = "19200"
        '
        'radioReader
        '
        Me.radioReader.AutoSize = True
        Me.radioReader.Enabled = False
        Me.radioReader.Location = New System.Drawing.Point(149, 19)
        Me.radioReader.Name = "radioReader"
        Me.radioReader.Size = New System.Drawing.Size(127, 17)
        Me.radioReader.TabIndex = 20
        Me.radioReader.TabStop = True
        Me.radioReader.Text = "Interface with Reader"
        Me.radioReader.UseVisualStyleBackColor = True
        '
        'cboPort
        '
        Me.cboPort.FormattingEnabled = True
        Me.cboPort.Location = New System.Drawing.Point(20, 47)
        Me.cboPort.Name = "cboPort"
        Me.cboPort.Size = New System.Drawing.Size(166, 21)
        Me.cboPort.TabIndex = 0
        Me.cboPort.Text = "Choose COM Port..."
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.GroupBox2)
        Me.GroupBox1.Controls.Add(Me.cboBaudRate)
        Me.GroupBox1.Controls.Add(Me.cboPort)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.cmdPortClose)
        Me.GroupBox1.Controls.Add(Me.cmdPortOpen)
        Me.GroupBox1.Location = New System.Drawing.Point(22, 1)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(421, 175)
        Me.GroupBox1.TabIndex = 21
        Me.GroupBox1.TabStop = False
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.Location = New System.Drawing.Point(326, 75)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(75, 48)
        Me.Label3.TabIndex = 22
        Me.Label3.Text = "Default " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "Baud Rate " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "is 19200"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.radioReader)
        Me.GroupBox2.Controls.Add(Me.radioPR29)
        Me.GroupBox2.Location = New System.Drawing.Point(23, 116)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(282, 47)
        Me.GroupBox2.TabIndex = 21
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Target Device"
        '
        'cmdGetTotal
        '
        Me.cmdGetTotal.Enabled = False
        Me.cmdGetTotal.Location = New System.Drawing.Point(134, 110)
        Me.cmdGetTotal.Name = "cmdGetTotal"
        Me.cmdGetTotal.Size = New System.Drawing.Size(88, 38)
        Me.cmdGetTotal.TabIndex = 22
        Me.cmdGetTotal.Text = "Get Total no." & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "Of Fingerprints"
        Me.cmdGetTotal.UseVisualStyleBackColor = True
        '
        'cmdAdd
        '
        Me.cmdAdd.Enabled = False
        Me.cmdAdd.Location = New System.Drawing.Point(6, 47)
        Me.cmdAdd.Name = "cmdAdd"
        Me.cmdAdd.Size = New System.Drawing.Size(92, 23)
        Me.cmdAdd.TabIndex = 24
        Me.cmdAdd.Text = "Add"
        Me.cmdAdd.UseVisualStyleBackColor = True
        '
        'cmdDelete
        '
        Me.cmdDelete.Enabled = False
        Me.cmdDelete.Location = New System.Drawing.Point(134, 47)
        Me.cmdDelete.Name = "cmdDelete"
        Me.cmdDelete.Size = New System.Drawing.Size(88, 23)
        Me.cmdDelete.TabIndex = 26
        Me.cmdDelete.Text = "Delete"
        Me.cmdDelete.UseVisualStyleBackColor = True
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.cmdAdd)
        Me.GroupBox3.Controls.Add(Me.cmdDelete)
        Me.GroupBox3.Controls.Add(Me.cmdTest)
        Me.GroupBox3.Controls.Add(Me.cmdGetTotal)
        Me.GroupBox3.Controls.Add(Me.cboUser)
        Me.GroupBox3.Location = New System.Drawing.Point(22, 205)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(228, 188)
        Me.GroupBox3.TabIndex = 27
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Commands"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(252, 186)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(97, 13)
        Me.Label4.TabIndex = 28
        Me.Label4.Text = "Attendance Viewer"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(21, 436)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(37, 13)
        Me.Label5.TabIndex = 29
        Me.Label5.Text = "Status"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(465, 533)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.txtStatus)
        Me.Controls.Add(Me.SaveTo)
        Me.Controls.Add(Me.OpenFile)
        Me.Controls.Add(Me.FileContents)
        Me.Controls.Add(Me.FileName)
        Me.Controls.Add(Me.StatusStrip1)
        Me.Controls.Add(Me.cmdReceive)
        Me.Controls.Add(Me.txtReceive)
        Me.Name = "Form1"
        Me.Text = "Fingerprint Reader GUI                           "
        Me.StatusStrip1.ResumeLayout(False)
        Me.StatusStrip1.PerformLayout()
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.GroupBox3.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents txtReceive As System.Windows.Forms.TextBox
    Friend WithEvents cmdReceive As System.Windows.Forms.Button
    Friend WithEvents SerialPort As System.IO.Ports.SerialPort
    Friend WithEvents ToolTip1 As System.Windows.Forms.ToolTip
    Friend WithEvents StatusStrip1 As System.Windows.Forms.StatusStrip
    Friend WithEvents StatusPanel As System.Windows.Forms.ToolStripStatusLabel
    Friend WithEvents cmdTest As System.Windows.Forms.Button
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents FileName As System.Windows.Forms.Label
    Friend WithEvents FileContents As System.Windows.Forms.TextBox
    Friend WithEvents OpenFile As System.Windows.Forms.Button
    Friend WithEvents SaveFileDialog1 As System.Windows.Forms.SaveFileDialog
    Friend WithEvents SaveTo As System.Windows.Forms.Button
    Friend WithEvents txtStatus As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents cmdPortClose As System.Windows.Forms.Button
    Friend WithEvents cmdPortOpen As System.Windows.Forms.Button
    Friend WithEvents radioPR29 As System.Windows.Forms.RadioButton
    Friend WithEvents cboBaudRate As System.Windows.Forms.ComboBox
    Friend WithEvents radioReader As System.Windows.Forms.RadioButton
    Friend WithEvents cboPort As System.Windows.Forms.ComboBox
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents cmdGetTotal As System.Windows.Forms.Button
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents cboUser As System.Windows.Forms.ComboBox
    Friend WithEvents cmdAdd As System.Windows.Forms.Button
    Friend WithEvents cmdDelete As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label

End Class
