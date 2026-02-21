object FormPIN: TFormPIN
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Login - PIN'
  ClientHeight = 604
  ClientWidth = 1031
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object Label1: TLabel
    Left = 408
    Top = 56
    Width = 211
    Height = 37
    Caption = 'CARD NUMBER :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 440
    Top = 200
    Width = 144
    Height = 37
    Caption = 'ENTER PIN:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object TEdit
    Left = 464
    Top = 264
    Width = 89
    Height = 23
    MaxLength = 4
    NumbersOnly = True
    PasswordChar = '*'
    ReadOnly = True
    TabOrder = 0
  end
  object TEdit
    Left = 376
    Top = 120
    Width = 265
    Height = 23
    MaxLength = 16
    NumbersOnly = True
    ReadOnly = True
    TabOrder = 1
  end
  object Button1: TButton
    Left = 160
    Top = 328
    Width = 41
    Height = 33
    Caption = '1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object Button2: TButton
    Left = 232
    Top = 328
    Width = 41
    Height = 33
    Caption = '2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
  end
  object Button3: TButton
    Left = 304
    Top = 328
    Width = 41
    Height = 33
    Caption = '3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 160
    Top = 400
    Width = 41
    Height = 33
    Caption = '4'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
  end
  object Button5: TButton
    Left = 232
    Top = 400
    Width = 41
    Height = 33
    Caption = '5'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
  end
  object Button6: TButton
    Left = 304
    Top = 400
    Width = 41
    Height = 33
    Caption = '6'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
  end
  object Button7: TButton
    Left = 160
    Top = 472
    Width = 41
    Height = 33
    Caption = '7'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
  end
  object Button8: TButton
    Left = 232
    Top = 472
    Width = 41
    Height = 33
    Caption = '8'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
  end
  object Button9: TButton
    Left = 304
    Top = 472
    Width = 41
    Height = 33
    Caption = '9'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
  end
  object Button0: TButton
    Left = 232
    Top = 539
    Width = 41
    Height = 33
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 11
  end
  object Btn_cancel: TButton
    Left = 752
    Top = 400
    Width = 89
    Height = 33
    Caption = 'CANCEL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
    OnClick = Btn_cancelClick
  end
  object btn_clearclic: TButton
    Left = 665
    Top = 328
    Width = 89
    Height = 33
    Caption = 'CLEAR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 13
    OnClick = Btn_clearclick
  end
  object Button10: TButton
    Left = 841
    Top = 328
    Width = 89
    Height = 33
    Caption = 'ENTER'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 14
  end
end
