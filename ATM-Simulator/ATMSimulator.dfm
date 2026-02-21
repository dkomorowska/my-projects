object FormStart: TFormStart
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'ATM Simulator'
  ClientHeight = 604
  ClientWidth = 1031
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  TextHeight = 15
  object Label1: TLabel
    Left = 320
    Top = 48
    Width = 384
    Height = 62
    Caption = 'ATM SIMULATOR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -47
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Btn_insertcard: TButton
    Left = 376
    Top = 264
    Width = 273
    Height = 73
    Caption = 'INSERT YOUR CARD'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = Btn_insertcardClick
  end
  object Btn_exit: TButton
    Left = 456
    Top = 536
    Width = 121
    Height = 25
    Caption = 'EXIT'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = Btn_exitClick
  end
end
