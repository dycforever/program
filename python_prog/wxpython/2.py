#!/bin/env python2.7
import wx
class DisFrame(wx.Frame):
    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)
        self.SetSize(wx.Size(600,400))
        self.SetTitle('Temperamental TextCtrl Tabs')
        # make a panel with a button / textctrl / listbox
        self.panel = wx.Panel(self)
        self.panel.SetFont(wx.Font(12, wx.NORMAL, wx.NORMAL, wx.NORMAL))
        bs = wx.BoxSizer(wx.VERTICAL)
        self.button = wx.Button(self.panel, -1,
                'Set Tabs and then Add Text')
        self.button.Bind(wx.EVT_BUTTON, self.ButtonClicked)
        bs.Add(self.button,0,wx.TOP|wx.LEFT|wx.RIGHT|wx.EXPAND,30)
        bs.AddSpacer(wx.Size(10,10))
        self.editor = wx.TextCtrl(self.panel,
                style=wx.TE_MULTILINE|wx.TE_PROCESS_TAB|wx.TE_RICH)

        bs.Add(self.editor,1,wx.EXPAND|wx.LEFT|wx.RIGHT,30)
        bs.AddSpacer(wx.Size(10,30))
        self.lb = wx.ListBox(self.panel, wx.NewId(), style=wx.LB_SINGLE)
        bs.Add(self.lb,2,wx.EXPAND|wx.BOTTOM|wx.LEFT|wx.RIGHT,30)
        self.panel.SetSizer(bs)
    def ButtonClicked(self, event):
        # change the default style of the textctrl,
        # set a few tab positions and then add
        # some text
        dastyle = wx.TextAttr()
        dastyle.SetTabs([200, 390, 800])
        self.editor.SetDefaultStyle(dastyle)
        # add text to the textctrl
        self.editor.Clear()
        self.editor.AppendText('\ttab1\ttab2\ttab3\n')
        x = 1
        for i in range(1,100):
            self.editor.AppendText(str(i)+'\t'+ ## line number adding and tab
                    5*('line ' + str(i)+'\t')+'\n')
            event.Skip()
if __name__ == '__main__':
    app = wx.App()
    daframe = DisFrame(None)
    daframe.Show()
    app.MainLoop()
