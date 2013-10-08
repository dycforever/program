#!/bin/env python2.7
import wx,os,re
ID_OPEN=102
ID_SAVE=103
ID_SaveAS=104
class MainWindow(wx.Frame):
    
    def __init__(self,parent,title):
        wx.Frame.__init__(self,parent,wx.ID_ANY, title)
        self.control = wx.TextCtrl(self, 1, style=wx.TE_MULTILINE)
        self.CreateStatusBar()
        filemenu= wx.Menu()
        filemenu.Append(ID_OPEN, "&Open", "Open a file to edit")
        filemenu.AppendSeparator()
        filemenu.Append(ID_SAVE, "&Save", "Saving the file")
        filemenu.Append(ID_SaveAS, "Save &As", "Saving file")
        menuBar = wx.MenuBar()
        menuBar.Append(filemenu,"&File")
        self.SetMenuBar(menuBar)
        wx.EVT_MENU(self, ID_OPEN, self.OnOpen)
        wx.EVT_MENU(self, ID_SAVE, self.OnSave)
        wx.EVT_MENU(self, ID_SaveAS, self.OnSaveAS)
        self.sizer2 = wx.BoxSizer(wx.HORIZONTAL)
        button = wx.Button(self, 1,"Parse HTML")
        self.sizer2.Add(button,1,wx.EXPAND)
        self.sizer=wx.BoxSizer(wx.VERTICAL)
        self.sizer.Add(self.control,1,wx.EXPAND)
        self.sizer.Add(self.sizer2,0,wx.EXPAND)
        self.SetSizer(self.sizer)
        self.SetAutoLayout(1)
        self.sizer.Fit(self)
        self.Bind(wx.EVT_BUTTON, self.checker, button)
        self.Show(1)
    def checker(self,e):
        f = open(self.filename, 'r')
        information = self.control.GetValue()
        b = re.findall('<\/?[^>]*>',information)
        a = ['<bml>','</bml>','<head>','</head>']
        b = information.split('\n')
        count = 0
        count1 = 0
        for line in b:
            count = count + 1
            if '<head>' in line:
                count1 = count1 + 1
            if count1 > 1 and '<head>' in line:
                box = wx.MessageDialog(None, "HTML Script can only contain 1 '<head>' tag." + '\n' + "Repeated <head> tag found in line: " + str(count), "Title",wx.OK)
                box = box.ShowModal()
                
    def OnSaveAS(self,e):
        dlg = wx.FileDialog(self, "Choose a file", self.filename, "", "*.*", wx.SAVE | wx.OVERWRITE_PROMPT)
        if dlg.ShowModal() == wx.ID_OK:
            grab = self.control.GetValue()
            f = open(self.filename, 'w')
            f.write(grab)
            f.close()
        dlg.DESTROY()
    def OnSave(self,e):
        grab = self.control.GetValue()
        f = open(self.filename, 'w')
        f.write(grab)
        f.close()
        box = wx.MessageDialog(None, "File Save Finish", "Title",wx.OK)
        box.ShowModal()
        box.Destroy
        
    def OnOpen(self, event):
        dlg = wx.FileDialog(self, "Open file...",style=wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetPath()
            f = open(self.filename, 'r')
            self.control.SetValue(f.read())
            self.SetTitle('Editing.....' + self.filename)
        line_number = len( self.control.GetRange( 0, self.control.GetInsertionPoint() ).split("\n") )
        print line_number
        dlg.Destroy()

app = wx.PySimpleApp()
frame = MainWindow(None, "Sample Editor")
frame.Show()
app.MainLoop()

