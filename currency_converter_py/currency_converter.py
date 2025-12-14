from tkinter import *
from tkinter import ttk, messagebox

#main window
root = Tk()
root.geometry('600x400+650+300')
root.attributes('-alpha', 0.92)
root.config(background='light grey')
root.title("Currency Converter")

icon_image = PhotoImage(file='icon.png')
root.call('wm', 'iconphoto', root._w, icon_image)

#title
my_label = Label(
    root,
    text='Currency Converter',
    font=('Open Sans', 20, 'bold'),
    bg='light grey'
)
my_label.grid(row=0, column=0, columnspan=2, padx=(170, 0), pady=(20, 10))

#rates
rates = {
    "PLN": 1.0,
    "EUR": 4.23,
    "USD": 3.65,
    "JPY": 0.023,
    "GBP": 4.81,
    "CNY": 0.51,
    "CHF": 4.52,
}

currencies = list(rates.keys())


#FUNCTIONS
def convert():
    text = amount_entry.get().strip()

    if text == "":
        messagebox.showerror("Error", "Please enter an amount")
        return

    text = text.replace(",", ".")

    try:
        amount = float(text)
    except ValueError:
        messagebox.showerror("Error", "Invalid amount: " + text)
        return

    if amount < 0:
        messagebox.showerror("Error", "Amount cannot be negative")
        return

    from_currency = from_combo.get()
    to_currency = to_combo.get()

    from_rate = rates[from_currency]
    to_rate = rates[to_currency]

    pln_amount = amount * from_rate
    result = pln_amount / to_rate

    result_text = (
        "Results: " + str(round(amount, 2)) + " " + from_currency
        + " = " + str(round(result, 2)) + " " + to_currency
    )
    result_label.config(text=result_text)


def clear():
    amount_entry.delete(0, END)
    result_label.config(text="Result: -")


def show_about():
    messagebox.showinfo(
        "About",
        "Currency Converter\n\n"
        "Simple desktop application written in Python (tkinter).\n"
        "It converts between PLN, EUR, USD, GBP, CHF, JPY and CNY.\n\n"
        "Author: Dominika Komorowska"
    )


#WIDGETS
amount_label = Label(root, text="Amount:", bg='light grey')
amount_label.grid(row=1, column=0, padx=(140, 5), pady=5, sticky="e")

amount_entry = Entry(root, width=15)
amount_entry.grid(row=1, column=1, padx=(0, 0), pady=5, sticky="w")

from_label = Label(root, text="From currency:", bg='light grey')
from_label.grid(row=2, column=0, padx=(140, 5), pady=5, sticky="e")

from_combo = ttk.Combobox(root, values=currencies,
                          state="readonly", width=12)
from_combo.current(0)  # default: PLN
from_combo.grid(row=2, column=1, padx=(0, 0), pady=5, sticky="w")

to_label = Label(root, text="To currency:", bg='light grey')
to_label.grid(row=3, column=0, padx=(140, 5), pady=5, sticky="e")

to_combo = ttk.Combobox(root, values=currencies,
                        state="readonly", width=12)
to_combo.current(1)  # default: EUR
to_combo.grid(row=3, column=1, padx=(0, 0), pady=5, sticky="w")

convert_button = Button(root, text="Convert", command=convert)
convert_button.grid(row=4, column=0, columnspan=2, padx=(158, 0), pady=(10, 5))

result_label = Label(root, text="Result: -", bg='light grey')
result_label.grid(row=5, column=0, columnspan=2, padx=(158, 0), pady=5)

clear_button = Button(root, text="Clear", command=clear)
clear_button.grid(row=6, column=0, columnspan=2, padx=(158, 0), pady=(10, 5))

about_button = Button(root, text="About", command=show_about)
about_button.grid(row=7, column=0, padx=(140, 5), pady=(20, 10), sticky="w")

exit_button = Button(root, text="Exit", command=root.quit)
exit_button.grid(row=7, column=2, padx=(0, 140), pady=(20, 10), sticky="e")

root.mainloop()
