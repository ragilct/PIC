Imports System.IO
Imports System
Imports System.Text
Imports Microsoft.VisualBasic.Strings


Public Class Form1

    Private Sub cbbComPort_DropDown( _
        ByVal sender As Object, ByVal e As System.EventArgs) _
        Handles cboPort.DropDown

        For i As Integer = 0 To My.Computer.Ports.SerialPortNames.Count - 1
            cboPort.Items.Clear()
            cboPort.Items.Add(My.Computer.Ports.SerialPortNames(i))
        Next

    End Sub
    Private Sub cmdPortOpen_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdPortOpen.Click
        If cboPort.Text = "Choose COM Port..." Then
            MsgBox("Please select COM Port", vbExclamation, "Message")
        Else
            SerialPort.PortName = cboPort.Text
            SerialPort.BaudRate = cboBaudRate.Text
            SerialPort.Encoding = System.Text.Encoding.ASCII

            Try
                SerialPort.Open()
                StatusPanel.Text = "Connected"
            Catch ex As Exception
                MsgBox(cboPort.Text & " already in used by other application.", vbExclamation, "Message")
                Exit Sub
            End Try
            cmdPortOpen.Enabled = False
            cmdPortClose.Enabled = True
            cmdReceive.Enabled = True
            cboPort.Enabled = False
            cboBaudRate.Enabled = False
            radioPR29.Enabled = True
            radioReader.Enabled = True
        End If

    End Sub

    Private Sub cmdPortClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdPortClose.Click
        SerialPort.Close()
        txtReceive.Text = ""
        StatusPanel.Text = "Not Connected"
        cboPort.Enabled = True
        cboBaudRate.Enabled = True
        cmdPortOpen.Enabled = True
        cmdPortClose.Enabled = False
        cmdGetTotal.Enabled = False
        cmdTest.Enabled = False
        SaveTo.Enabled = False
        OpenFile.Enabled = False
        cmdReceive.Enabled = False
        FileContents.Text = ""
        FileContents.Enabled = False
        FileName.Enabled = False
        txtReceive.Enabled = False
        txtStatus.Enabled = False
        radioPR29.Enabled = False
        radioReader.Enabled = False
        radioPR29.Checked = False
        radioReader.Checked = False
        txtStatus.Text = ""
        cboPort.Text = "Choose COM Port..."
        cboBaudRate.Text = "19200"
        cboUser.Text = "Choose User..."

    End Sub



    Private Sub cmdReceive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdReceive.Click


        txtReceive.Text = SerialPort.ReadExisting()
        'cmdMove.Enabled = True
        If txtReceive.Text = "" Then
            txtStatus.Text = "Failed to Import Attendance"
        Else
            ' Dim oWriter As New (FileContents.Text)
            Dim DAY1, D1U1, D1U2, D1U3, D1U4, D1U5 As String
            Dim DAY2, D2U1, D2U2, D2U3, D2U4, D2U5 As String
            Dim DAY3, D3U1, D3U2, D3U3, D3U4, D3U5 As String
            Dim DAY4, D4U1, D4U2, D4U3, D4U4, D4U5 As String
            Dim DAY5, D5U1, D5U2, D5U3, D5U4, D5U5 As String

            ' If Not (oWriter Is Nothing) Then
            DAY1 = txtReceive.Text.Substring(0, 4)
            D1U1 = txtReceive.Text.Substring(4, 1)
            D1U2 = txtReceive.Text.Substring(5, 1)
            D1U3 = txtReceive.Text.Substring(6, 1)
            D1U4 = txtReceive.Text.Substring(7, 1)
            D1U5 = txtReceive.Text.Substring(8, 1)

            DAY2 = txtReceive.Text.Substring(9, 4)
            D2U1 = txtReceive.Text.Substring(13, 1)
            D2U2 = txtReceive.Text.Substring(14, 1)
            D2U3 = txtReceive.Text.Substring(15, 1)
            D2U4 = txtReceive.Text.Substring(16, 1)
            D2U5 = txtReceive.Text.Substring(17, 1)

            DAY3 = txtReceive.Text.Substring(18, 4)
            D3U1 = txtReceive.Text.Substring(22, 1)
            D3U2 = txtReceive.Text.Substring(23, 1)
            D3U3 = txtReceive.Text.Substring(24, 1)
            D3U4 = txtReceive.Text.Substring(25, 1)
            D3U5 = txtReceive.Text.Substring(26, 1)

            DAY4 = txtReceive.Text.Substring(27, 4)
            D4U1 = txtReceive.Text.Substring(31, 1)
            D4U2 = txtReceive.Text.Substring(32, 1)
            D4U3 = txtReceive.Text.Substring(33, 1)
            D4U4 = txtReceive.Text.Substring(34, 1)
            D4U5 = txtReceive.Text.Substring(35, 1)

            DAY5 = txtReceive.Text.Substring(36, 4)
            D5U1 = txtReceive.Text.Substring(40, 1)
            D5U2 = txtReceive.Text.Substring(41, 1)
            D5U3 = txtReceive.Text.Substring(42, 1)
            D5U4 = txtReceive.Text.Substring(43, 1)
            D5U5 = txtReceive.Text.Substring(44, 1)

            txtReceive.Text = ""
            'Then use the TextBox to get the contents.
            FileContents.Text = "+-+-+-+Cytron PR29+-+-+-+-+"
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & "USER   1   2   3   4   5"
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & DAY1 & "   " & D1U1 & "   " & D1U2 & "   " & D1U3 & "   " & D1U4 & "   " & D1U5
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & DAY2 & "   " & D2U1 & "   " & D2U2 & "   " & D2U3 & "   " & D2U4 & "   " & D2U5
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & DAY3 & "   " & D3U1 & "   " & D3U2 & "   " & D3U3 & "   " & D3U4 & "   " & D3U5
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & DAY4 & "   " & D4U1 & "   " & D4U2 & "   " & D4U3 & "   " & D4U4 & "   " & D4U5
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & DAY5 & "   " & D5U1 & "   " & D5U2 & "   " & D5U3 & "   " & D5U4 & "   " & D5U5
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & vbCrLf
            FileContents.Text = FileContents.Text & "+-+-+-+-+-+-+-+-+-+-+-+-+-+"


            FileContents.Enabled = True
            SaveTo.Enabled = True
            OpenFile.Enabled = True
            txtStatus.Text = "Attendance Imported Successfully"
        End If


    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        StatusPanel.Text = "Not Connected"
        cmdTest.Enabled = False
        SaveTo.Enabled = False
        OpenFile.Enabled = False
        cmdReceive.Enabled = False
        FileContents.Enabled = False
        FileName.Enabled = False
        txtReceive.Enabled = False
        txtStatus.Enabled = False

    End Sub

    Private Sub cmdTest_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdTest.Click
        txtReceive.Text = ""
        txtStatus.Text = "Place Your Thumb On the Window"
        txtReceive.Refresh()
        txtStatus.Refresh()

        Dim buff() As Byte = {&HF5, &HC, &H0, &H0, &H0, &H0, &HC, &HF5}

        Dim i As Short
        Dim a As Short

        For i = 0 To 7
            SerialPort.Write(buff, i, 1)
        Next i

        While a = 0
            a = checkbuffer(8)
        End While
        checkstatus()


    End Sub


    Dim myFileContents As String
    Private Sub OpenFile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenFile.Click
        'Open the dialog and make sure it was successful
        If OpenFileDialog1.ShowDialog() = DialogResult.OK Then
            'Open a streamreader with the file name from the dialog
            Dim myStreamReader As New  _
            StreamReader(OpenFileDialog1.FileName)
            'Read the file with the streamreader
            Dim myFileContents As String = myStreamReader.ReadToEnd()
            'Close the streamreader - it uses resources
            myStreamReader.Close()
            'Set the output fields
            FileName.Text = OpenFileDialog1.FileName.ToString
            FileContents.Text = myFileContents
        End If
    End Sub

    Private Sub SaveTo_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveTo.Click
        SaveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*"
        SaveFileDialog1.FilterIndex = 1     'make .txt file is default file type to save
        SaveFileDialog1.RestoreDirectory = True
        If SaveFileDialog1.ShowDialog() = DialogResult.OK Then
            Dim oWriter As New StreamWriter(SaveFileDialog1.FileName)
            oWriter.Write(FileContents.Text)
            oWriter.Close()
        End If
    End Sub

    Private Sub cmdMove_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)


        Dim DAY1, D1U1, D1U2, D1U3, D1U4, D1U5 As String
        Dim DAY2, D2U1, D2U2, D2U3, D2U4, D2U5 As String
        Dim DAY3, D3U1, D3U2, D3U3, D3U4, D3U5 As String
        Dim DAY4, D4U1, D4U2, D4U3, D4U4, D4U5 As String
        Dim DAY5, D5U1, D5U2, D5U3, D5U4, D5U5 As String


        DAY1 = txtReceive.Text.Substring(0, 4)
        D1U1 = txtReceive.Text.Substring(4, 1)
        D1U2 = txtReceive.Text.Substring(5, 1)
        D1U3 = txtReceive.Text.Substring(6, 1)
        D1U4 = txtReceive.Text.Substring(7, 1)
        D1U5 = txtReceive.Text.Substring(8, 1)

        DAY2 = txtReceive.Text.Substring(9, 4)
        D2U1 = txtReceive.Text.Substring(13, 1)
        D2U2 = txtReceive.Text.Substring(14, 1)
        D2U3 = txtReceive.Text.Substring(15, 1)
        D2U4 = txtReceive.Text.Substring(16, 1)
        D2U5 = txtReceive.Text.Substring(17, 1)

        DAY3 = txtReceive.Text.Substring(18, 4)
        D3U1 = txtReceive.Text.Substring(22, 1)
        D3U2 = txtReceive.Text.Substring(23, 1)
        D3U3 = txtReceive.Text.Substring(24, 1)
        D3U4 = txtReceive.Text.Substring(25, 1)
        D3U5 = txtReceive.Text.Substring(26, 1)

        DAY4 = txtReceive.Text.Substring(27, 4)
        D4U1 = txtReceive.Text.Substring(31, 1)
        D4U2 = txtReceive.Text.Substring(32, 1)
        D4U3 = txtReceive.Text.Substring(33, 1)
        D4U4 = txtReceive.Text.Substring(34, 1)
        D4U5 = txtReceive.Text.Substring(35, 1)

        DAY5 = txtReceive.Text.Substring(36, 4)
        D5U1 = txtReceive.Text.Substring(40, 1)
        D5U2 = txtReceive.Text.Substring(41, 1)
        D5U3 = txtReceive.Text.Substring(42, 1)
        D5U4 = txtReceive.Text.Substring(43, 1)
        D5U5 = txtReceive.Text.Substring(44, 1)


        FileContents.Text = "+-+-+-+Cytron PR29+-+-+-+-+"
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & "USER   1   2   3   4   5"
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & DAY1 & "   " & D1U1 & "   " & D1U2 & "   " & D1U3 & "   " & D1U4 & "   " & D1U5
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & DAY2 & "   " & D2U1 & "   " & D2U2 & "   " & D2U3 & "   " & D2U4 & "   " & D2U5
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & DAY3 & "   " & D3U1 & "   " & D3U2 & "   " & D3U3 & "   " & D3U4 & "   " & D3U5
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & DAY4 & "   " & D4U1 & "   " & D4U2 & "   " & D4U3 & "   " & D4U4 & "   " & D4U5
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & DAY5 & "   " & D5U1 & "   " & D5U2 & "   " & D5U3 & "   " & D5U4 & "   " & D5U5
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & vbCrLf
        FileContents.Text = FileContents.Text & "+-+-+-+-+-+-+-+-+-+-+-+-+-+"
        FileContents.Enabled = True
        SaveTo.Enabled = True
        OpenFile.Enabled = True

    End Sub


    ' VB.NET to convert a string to a byte array
    Public Shared Function StrToByteArray(ByVal str As String) As Byte()
        Dim encoding As New System.Text.ASCIIEncoding()
        Return encoding.GetBytes(str)
    End Function

    Private Sub radioPR29_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles radioPR29.CheckedChanged
        txtReceive.Text = ""
        txtStatus.Text = ""
        cmdTest.Enabled = False
        cmdGetTotal.Enabled = False
        SaveTo.Enabled = False
        OpenFile.Enabled = False
        cmdReceive.Enabled = True
        FileContents.Enabled = False
        FileName.Enabled = False
        txtReceive.Enabled = True
        txtStatus.Enabled = True
        cboUser.Enabled = False
        cmdAdd.Enabled = False
        cmdDelete.Enabled = False
        cmdReceive.Enabled = True


    End Sub

    Private Sub radioReader_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles radioReader.CheckedChanged
        txtReceive.Text = ""
        txtStatus.Text = ""
        cmdTest.Enabled = True
        cmdGetTotal.Enabled = True
        SaveTo.Enabled = False
        OpenFile.Enabled = False
        cmdReceive.Enabled = True
        FileContents.Enabled = False
        FileName.Enabled = False
        txtReceive.Enabled = True
        txtStatus.Enabled = True
        cboUser.Enabled = True
        cmdAdd.Enabled = True
        cmdDelete.Enabled = True
        cmdReceive.Enabled = False

    End Sub


    Private Sub cmdGetTotal_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdGetTotal.Click
        Dim Buff() As Byte = {&HF5, &H9, &H0, &H0, &H0, &H0, &H9, &HF5}
        Dim i As Short
        Dim a As Short = 0
        txtReceive.Text = ""
        txtStatus.Text = ""
        For i = 0 To 7
            SerialPort.Write(Buff, i, 1)
        Next i
        While a = 0
            a = checkbuffer(8)
        End While

        checkstatus()

    End Sub

    Public Function checkbuffer(ByVal lenght As Byte) As Byte

        Dim flag As Byte
        If SerialPort.BytesToRead < lenght Then

            flag = 0
            Return flag
        Else

            flag = 1
            Return flag
        End If
    End Function


    Public Function checkstatus() As Byte
        If radioReader.Checked = True Then
            Dim number As Byte()
            Dim receivedData As String = ""
            Dim error1 As Byte = 0
            receivedData += SerialPort.ReadExisting()
            number = StrToByteArray(receivedData)
            txtReceive.Text = BitConverter.ToString(number)

            If Len(BitConverter.ToString(number)) = 23 Then
                Select Case number(1)
                    Case 12 ' 0X0C is decimal 12 reply of 1:N
                        If number(4) = 3 Then
                            Select Case number(3)
                                Case 63
                                    txtStatus.Text = "Welcome Admin"
                                Case 1
                                    txtStatus.Text = "Welcome User 1"
                                Case 2
                                    txtStatus.Text = "Welcome User 2"
                                Case 3
                                    txtStatus.Text = "Welcome User 3"
                                Case 4
                                    txtStatus.Text = "Welcome User 4"
                                Case 5
                                    txtStatus.Text = "Welcome User 5"
                                Case Else
                                    txtStatus.Text = "Welcome User"
                            End Select

                        ElseIf number(4) = 8 Then
                            txtStatus.Text = "Time Out"
                        Else
                            txtStatus.Text = "User Not Found"
                        End If
                    Case 9
                        txtStatus.Text = "No. of fingerprints collected = " & number(3)

                    Case 1
                        Select Case number(4)
                            Case 0
                                txtStatus.Text = "Again-Verification 1/2"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 0
                                Return error1
                            Case 1
                                txtStatus.Text = "Error!"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case 4
                                txtStatus.Text = "Full!"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case 7
                                txtStatus.Text = "Error: User exists"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case 8
                                txtStatus.Text = "Time out"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case Else
                                txtStatus.Text = "Unknown Error!"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                        End Select
                    Case 2
                        Select Case number(4)
                            Case 0
                                txtStatus.Text = "Again-Verification 2/2"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 0
                                Return error1
                            Case 1
                                txtStatus.Text = "Error!"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case 4
                                txtStatus.Text = "Full!"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case 7
                                txtStatus.Text = "Error: User exists"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case 8
                                txtStatus.Text = "Time out"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                            Case Else
                                txtStatus.Text = "Unknown Error!"
                                txtStatus.Refresh()
                                System.Threading.Thread.Sleep(1000)
                                error1 = 1
                                Return error1
                        End Select
                    Case 3
                        Select Case number(4)
                            Case 0
                                txtStatus.Text = "Added Successfully"
                                error1 = 0
                                Return error1
                            Case 1
                                txtStatus.Text = "Error!"
                                error1 = 1
                                Return error1
                            Case 4
                                txtStatus.Text = "Full!"
                                error1 = 1
                                Return error1
                            Case 7
                                txtStatus.Text = "Error: User exists"
                                error1 = 1
                                Return error1
                            Case 8
                                txtStatus.Text = "Time out"
                                error1 = 1
                                Return error1
                            Case Else
                                txtStatus.Text = "Unknown Error!"
                                error1 = 1
                                Return error1
                        End Select
                    Case 4
                        Select Case number(4)
                            Case 0
                                txtStatus.Text = "Deleted Successfully"
                                error1 = 0
                                Return error1
                            Case 1
                                txtStatus.Text = "Error!"
                                error1 = 1
                                Return error1
                        End Select
                End Select

            Else
                txtStatus.Text = "No data??"
            End If
        End If

        If radioPR29.Checked = True Then
            txtReceive.Text = SerialPort.ReadExisting()

        End If

    End Function


    Private Sub cmdAdd_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdAdd.Click
        Dim i As Short
        Dim a As Short
        Dim error1 As Short
        txtReceive.Text = ""
        txtStatus.Text = "Place Your Thumb On the Window"
        txtReceive.Refresh()
        txtStatus.Refresh()

        If cboUser.Text = "Choose User..." Then
            MsgBox(" Please Select User ", vbExclamation, "Message")
        ElseIf cboUser.Text = "User 1" Then
            Dim user1_1() As Byte = {&HF5, &H1, &H0, &H1, &H3, &H0, &H3, &HF5} 'F5-01-00-01-03-00-03-F5
            Dim user1_2() As Byte = {&HF5, &H2, &H0, &H1, &H3, &H0, &H0, &HF5}
            Dim user1_3() As Byte = {&HF5, &H3, &H0, &H1, &H3, &H0, &H1, &HF5}

            For i = 0 To 7
                SerialPort.Write(user1_1, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            error1 = checkstatus()
            If error1 = 0 Then
                For i = 0 To 7
                    SerialPort.Write(user1_2, i, 1)
                Next i
                a = 0
                While a = 0
                    a = checkbuffer(8)
                End While
                error1 = checkstatus()
                If error1 = 0 Then
                    For i = 0 To 7
                        SerialPort.Write(user1_3, i, 1)
                    Next i
                    a = 0
                    While a = 0
                        a = checkbuffer(8)
                    End While
                    error1 = checkstatus()

                End If

            End If
        ElseIf cboUser.Text = "User 2" Then
            Dim user2_1() As Byte = {&HF5, &H1, &H0, &H2, &H3, &H0, &H0, &HF5}
            Dim user2_2() As Byte = {&HF5, &H2, &H0, &H2, &H3, &H0, &H3, &HF5}
            Dim user2_3() As Byte = {&HF5, &H3, &H0, &H2, &H3, &H0, &H2, &HF5}


            For i = 0 To 7
                SerialPort.Write(user2_1, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            error1 = checkstatus()
            If error1 = 0 Then
                For i = 0 To 7
                    SerialPort.Write(user2_2, i, 1)
                Next i
                a = 0
                While a = 0
                    a = checkbuffer(8)
                End While
                error1 = checkstatus()
                If error1 = 0 Then
                    For i = 0 To 7
                        SerialPort.Write(user2_3, i, 1)
                    Next i
                    a = 0
                    While a = 0
                        a = checkbuffer(8)
                    End While
                    error1 = checkstatus()

                End If

            End If
        ElseIf cboUser.Text = "User 3" Then
            Dim user3_1() As Byte = {&HF5, &H1, &H0, &H3, &H3, &H0, &H1, &HF5}
            Dim user3_2() As Byte = {&HF5, &H2, &H0, &H3, &H3, &H0, &H2, &HF5}
            Dim user3_3() As Byte = {&HF5, &H3, &H0, &H3, &H3, &H0, &H3, &HF5}


            For i = 0 To 7
                SerialPort.Write(user3_1, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            error1 = checkstatus()
            If error1 = 0 Then
                For i = 0 To 7
                    SerialPort.Write(user3_2, i, 1)
                Next i
                a = 0
                While a = 0
                    a = checkbuffer(8)
                End While
                error1 = checkstatus()
                If error1 = 0 Then
                    For i = 0 To 7
                        SerialPort.Write(user3_3, i, 1)
                    Next i
                    a = 0
                    While a = 0
                        a = checkbuffer(8)
                    End While
                    error1 = checkstatus()

                End If

            End If
        ElseIf cboUser.Text = "User 4" Then
            Dim user4_1() As Byte = {&HF5, &H1, &H0, &H4, &H3, &H0, &H6, &HF5}
            Dim user4_2() As Byte = {&HF5, &H2, &H0, &H4, &H3, &H0, &H5, &HF5}
            Dim user4_3() As Byte = {&HF5, &H3, &H0, &H4, &H3, &H0, &H4, &HF5}


            For i = 0 To 7
                SerialPort.Write(user4_1, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            error1 = checkstatus()
            If error1 = 0 Then
                For i = 0 To 7
                    SerialPort.Write(user4_2, i, 1)
                Next i
                a = 0
                While a = 0
                    a = checkbuffer(8)
                End While
                error1 = checkstatus()
                If error1 = 0 Then
                    For i = 0 To 7
                        SerialPort.Write(user4_3, i, 1)
                    Next i
                    a = 0
                    While a = 0
                        a = checkbuffer(8)
                    End While
                    error1 = checkstatus()

                End If

            End If
        ElseIf cboUser.Text = "User 5" Then
            Dim user5_1() As Byte = {&HF5, &H1, &H0, &H5, &H3, &H0, &H7, &HF5}
            Dim user5_2() As Byte = {&HF5, &H2, &H0, &H5, &H3, &H0, &H6, &HF5}
            Dim user5_3() As Byte = {&HF5, &H3, &H0, &H5, &H3, &H0, &H5, &HF5}


            For i = 0 To 7
                SerialPort.Write(user5_1, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            error1 = checkstatus()
            If error1 = 0 Then
                For i = 0 To 7
                    SerialPort.Write(user5_2, i, 1)
                Next i
                a = 0
                While a = 0
                    a = checkbuffer(8)
                End While
                checkstatus()
                If error1 = 0 Then
                    For i = 0 To 7
                        SerialPort.Write(user5_3, i, 1)
                    Next i
                    a = 0
                    While a = 0
                        a = checkbuffer(8)
                    End While
                    checkstatus()

                End If

            End If
        End If

    End Sub

    Private Sub cmdDelete_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdDelete.Click
        Dim a As Byte
        Dim i As Short
        If cboUser.Text = "Choose User..." Then
            MsgBox(" Please Select User ", vbExclamation, "Message")
        ElseIf cboUser.Text = "User 1" Then
            Dim delete1() As Byte = {&HF5, &H4, &H0, &H1, &H0, &H0, &H5, &HF5}
            For i = 0 To 7
                SerialPort.Write(delete1, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            checkstatus()
        ElseIf cboUser.Text = "User 2" Then
            Dim delete2() As Byte = {&HF5, &H4, &H0, &H2, &H0, &H0, &H6, &HF5}
            For i = 0 To 7
                SerialPort.Write(delete2, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            checkstatus()
        ElseIf cboUser.Text = "User 3" Then
            Dim delete3() As Byte = {&HF5, &H4, &H0, &H3, &H0, &H0, &H7, &HF5}
            For i = 0 To 7
                SerialPort.Write(delete3, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            checkstatus()
        ElseIf cboUser.Text = "User 4" Then
            Dim delete4() As Byte = {&HF5, &H4, &H0, &H4, &H0, &H0, &H0, &HF5}
            For i = 0 To 7
                SerialPort.Write(delete4, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            checkstatus()
        ElseIf cboUser.Text = "User 5" Then
            Dim delete5() As Byte = {&HF5, &H4, &H0, &H5, &H0, &H0, &H1, &HF5}
            For i = 0 To 7
                SerialPort.Write(delete5, i, 1)
            Next i
            a = 0
            While a = 0
                a = checkbuffer(8)
            End While
            checkstatus()
        End If

    End Sub

    Private Sub cboUser_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cboUser.SelectedIndexChanged
        txtReceive.Text = ""
        txtStatus.Text = ""
    End Sub

    Private Sub cboUser2_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs)
        txtReceive.Text = ""
        txtStatus.Text = ""
    End Sub


End Class
