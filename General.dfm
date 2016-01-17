object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 864
  ClientWidth = 833
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 219
    Top = 24
    Width = 3
    Height = 13
  end
  object Label2: TLabel
    Left = 219
    Top = 88
    Width = 3
    Height = 13
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 219
    Top = 152
    Width = 3
    Height = 13
  end
  object Label4: TLabel
    Left = 219
    Top = 216
    Width = 3
    Height = 13
  end
  object Label5: TLabel
    Left = 219
    Top = 280
    Width = 3
    Height = 13
  end
  object Label6: TLabel
    Left = 219
    Top = 344
    Width = 3
    Height = 13
  end
  object Label7: TLabel
    Left = 219
    Top = 408
    Width = 3
    Height = 13
  end
  object Label8: TLabel
    Left = 219
    Top = 472
    Width = 3
    Height = 13
  end
  object Label9: TLabel
    Left = 219
    Top = 536
    Width = 3
    Height = 13
  end
  object Button1: TButton
    Left = 24
    Top = 24
    Width = 161
    Height = 41
    Caption = 'Test Connection'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 24
    Top = 88
    Width = 161
    Height = 41
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' token'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 24
    Top = 152
    Width = 161
    Height = 41
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1090#1080#1087#1099' '#1079#1072#1087#1088#1086#1089#1086#1074
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 24
    Top = 216
    Width = 161
    Height = 41
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1090#1080#1087#1099' '#1086#1073#1098#1077#1082#1090#1086#1074
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 24
    Top = 280
    Width = 161
    Height = 41
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1090#1072#1088#1080#1092#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 24
    Top = 344
    Width = 161
    Height = 41
    Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1087#1077#1088#1077#1076' '#1079#1072#1082#1072#1079#1086#1084
    TabOrder = 5
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 24
    Top = 408
    Width = 161
    Height = 41
    Caption = #1057#1086#1079#1076#1072#1090#1100' '#1079#1072#1087#1088#1086#1089
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 24
    Top = 472
    Width = 161
    Height = 41
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1079#1072#1087#1088#1086#1089#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 24
    Top = 536
    Width = 161
    Height = 41
    Caption = #1048#1089#1090#1086#1088#1080#1103' '#1079#1072#1087#1088#1086#1089#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 24
    Top = 600
    Width = 161
    Height = 41
    Caption = #1058#1077#1089#1090#1080#1088#1091#1077#1084' '#1079#1072#1075#1088#1091#1079#1082#1091' Token'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    OnClick = Button10Click
  end
  object IdHTTP1: TIdHTTP
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 448
    Top = 112
  end
end
