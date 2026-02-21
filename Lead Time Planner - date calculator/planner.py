import tkinter as tk
from tkinter import ttk, messagebox, filedialog

from tkcalendar import DateEntry
from datetime import date, timedelta
import csv


def weeks_and_days(delta_days: int):
    """Zamienia dni na (tygodnie, reszta dni) z zachowaniem znaku."""
    sign = -1 if delta_days < 0 else 1
    abs_days = abs(delta_days)
    weeks = abs_days // 7
    rest_days = abs_days % 7
    return sign * weeks, sign * rest_days


PL_MONTHS = {
    1: "stycznia", 2: "lutego", 3: "marca", 4: "kwietnia", 5: "maja", 6: "czerwca",
    7: "lipca", 8: "sierpnia", 9: "września", 10: "października", 11: "listopada", 12: "grudnia"
}

EN_MONTHS = {
    1: "January", 2: "February", 3: "March", 4: "April", 5: "May", 6: "June",
    7: "July", 8: "August", 9: "September", 10: "October", 11: "November", 12: "December"
}


def format_range_pl(d_start: date, d_end: date) -> str:
    same_year = (d_start.year == d_end.year)
    same_month = (d_start.month == d_end.month)

    if same_year and same_month:
        return f"{d_start.day}–{d_end.day} {PL_MONTHS[d_start.month]} {d_start.year}"
    if same_year:
        return f"{d_start.day} {PL_MONTHS[d_start.month]} – {d_end.day} {PL_MONTHS[d_end.month]} {d_start.year}"
    return (
        f"{d_start.day} {PL_MONTHS[d_start.month]} {d_start.year} – "
        f"{d_end.day} {PL_MONTHS[d_end.month]} {d_end.year}"
    )


def format_range_en(d_start: date, d_end: date) -> str:
    same_year = (d_start.year == d_end.year)
    same_month = (d_start.month == d_end.month)

    if same_year and same_month:
        return f"{EN_MONTHS[d_start.month]} {d_start.day}–{d_end.day}, {d_start.year}"
    if same_year:
        return f"{EN_MONTHS[d_start.month]} {d_start.day} – {EN_MONTHS[d_end.month]} {d_end.day}, {d_start.year}"
    return f"{EN_MONTHS[d_start.month]} {d_start.day}, {d_start.year} – {EN_MONTHS[d_end.month]} {d_end.day}, {d_end.year}"


class PlannerApp(tk.Tk):
    def __init__(self):
        super().__init__()

        # Tytuł okna (zgodnie z Twoją prośbą)
        self.title("Lead Time Planner - date calculator")
        self.geometry("1100x640")
        self.minsize(980, 560)

        # Język aplikacji: "pl" albo "en"
        self.lang = tk.StringVar(value="pl")

        # Historia operacji
        self.history = []

        # Tłumaczenia (prosto, "jak początkujący")
        self.T = {
            "pl": {
                "language": "Język:",
                "pl": "Polski",
                "en": "English",

                "section_diff": "Różnica między datami",
                "section_add": "Data + N dni",
                "section_week": "Tydzień → zakres dat",

                "date1": "Data 1:",
                "date2": "Data 2:",
                "mode": "Tryb:",
                "calendar": "kalendarzowe",
                "business": "robocze (pn-pt)",
                "count": "Policz",

                "base_date": "Data bazowa:",
                "n_days": "N dni:",

                "year": "Rok:",
                "week": "Tydzień:",
                "show_range": "Pokaż zakres",

                "history": "Historia",
                "select_hint": "Zaznacz wpis, żeby zobaczyć szczegóły.",

                "copy": "Kopiuj zazn.",
                "delete": "Usuń zazn.",
                "export": "Eksport CSV",
                "clear": "Wyczyść",

                "diff_result": "Różnica: {days} dni | {weeks} tyg. i {rest} dni",
                "add_result": "Wynik: {target}",  # <-- tu już NIE MA tygodnia
                "week_result": "Tydzień {w} ({y}): {start} – {end}  |  {pretty}",

                "type_diff": "Typ: Różnica dat",
                "type_add": "Typ: Data + N dni",
                "type_week": "Typ: Tydzień → zakres dat",

                "err_title": "Błąd",
                "err_bad_week": "Nieprawidłowy tydzień dla podanego roku (spróbuj inny numer).",

                "info_title": "Info",
                "info_no_selection": "Nie wybrano wpisu.",
                "info_empty_history": "Historia jest pusta.",

                "ok_title": "OK",
                "ok_exported": "Wyeksportowano do:\n{path}",

                "deleted": "Usunięto wpis.",
                "cleared": "Historia wyczyszczona.",
            },
            "en": {
                "language": "Language:",
                "pl": "Polish",
                "en": "English",

                "section_diff": "Date difference",
                "section_add": "Date + N days",
                "section_week": "Week → date range",

                "date1": "Date 1:",
                "date2": "Date 2:",
                "mode": "Mode:",
                "calendar": "calendar days",
                "business": "business days (Mon–Fri)",
                "count": "Calculate",

                "base_date": "Base date:",
                "n_days": "N days:",

                "year": "Year:",
                "week": "Week:",
                "show_range": "Show range",

                "history": "History",
                "select_hint": "Select an entry to see details.",

                "copy": "Copy selected",
                "delete": "Delete selected",
                "export": "Export CSV",
                "clear": "Clear",

                "diff_result": "Difference: {days} days | {weeks} weeks and {rest} days",
                "add_result": "Result: {target}",  # <-- tu też bez tygodnia
                "week_result": "Week {w} ({y}): {start} – {end}  |  {pretty}",

                "type_diff": "Type: Date difference",
                "type_add": "Type: Date + N days",
                "type_week": "Type: Week → date range",

                "err_title": "Error",
                "err_bad_week": "Invalid week for the given year (try another number).",

                "info_title": "Info",
                "info_no_selection": "No entry selected.",
                "info_empty_history": "History is empty.",

                "ok_title": "OK",
                "ok_exported": "Exported to:\n{path}",

                "deleted": "Entry deleted.",
                "cleared": "History cleared.",
            }
        }


        self.build_ui()
        self.apply_language()

    def tr(self, key: str) -> str:
        """Zwraca tekst w aktualnym języku."""
        return self.T[self.lang.get()][key]


    def business_days_between(self, d1: date, d2: date) -> int:
        if d1 == d2:
            return 0

        step = 1 if d2 > d1 else -1
        cur = d1
        count = 0

        while cur != d2:
            cur = cur + timedelta(days=step)
            if cur.weekday() < 5:
                count += step

        return count


    # UI

    def build_ui(self):
        today = date.today()

        main = ttk.Frame(self, padding=12)
        main.grid(row=0, column=0, sticky="nsew")

        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        main.grid_columnconfigure(0, weight=3)
        main.grid_columnconfigure(1, weight=2)
        main.grid_rowconfigure(0, weight=1)

        left = ttk.Frame(main)
        left.grid(row=0, column=0, sticky="nsew", padx=(0, 10))
        left.grid_columnconfigure(0, weight=1)

        right = ttk.Frame(main)
        right.grid(row=0, column=1, sticky="nsew")
        right.grid_rowconfigure(1, weight=1)
        right.grid_columnconfigure(0, weight=1)


        topbar = ttk.Frame(left)
        topbar.grid(row=0, column=0, sticky="ew", pady=(0, 10))
        topbar.grid_columnconfigure(1, weight=1)

        self.lbl_language = ttk.Label(topbar, text="")  # tekst ustawimy w apply_language()
        self.lbl_language.grid(row=0, column=0, sticky="w")

        self.lang_combo = ttk.Combobox(
            topbar,
            state="readonly",
            values=["pl", "en"],
            width=8,
            textvariable=self.lang
        )
        self.lang_combo.grid(row=0, column=1, sticky="w", padx=8)
        self.lang_combo.bind("<<ComboboxSelected>>", lambda _e: self.apply_language())


        self.h_diff = ttk.Label(left, text="", font=("Segoe UI", 11, "bold"))
        self.h_diff.grid(row=1, column=0, sticky="w", pady=(0, 6))

        sec_a = ttk.Frame(left, padding=10, relief="groove")
        sec_a.grid(row=2, column=0, sticky="ew", pady=(0, 22))
        for c in range(4):
            sec_a.grid_columnconfigure(c, weight=1)

        self.lbl_d1 = ttk.Label(sec_a, text="")
        self.lbl_d1.grid(row=0, column=0, sticky="w")

        self.d1 = DateEntry(sec_a, date_pattern="yyyy-mm-dd")
        self.d1.set_date(today)
        self.d1.grid(row=0, column=1, padx=8, pady=4, sticky="w")

        self.lbl_d2 = ttk.Label(sec_a, text="")
        self.lbl_d2.grid(row=0, column=2, sticky="w")

        self.d2 = DateEntry(sec_a, date_pattern="yyyy-mm-dd")
        self.d2.set_date(today)
        self.d2.grid(row=0, column=3, padx=8, pady=4, sticky="w")

        self.lbl_mode = ttk.Label(sec_a, text="")
        self.lbl_mode.grid(row=1, column=0, sticky="w", pady=(6, 0))

        self.mode = tk.StringVar(value="kalendarzowe")

        self.rb_calendar = ttk.Radiobutton(sec_a, text="", variable=self.mode, value="kalendarzowe")
        self.rb_calendar.grid(row=1, column=1, sticky="w", pady=(6, 0))

        self.rb_business = ttk.Radiobutton(sec_a, text="", variable=self.mode, value="robocze")
        self.rb_business.grid(row=1, column=2, sticky="w", pady=(6, 0))

        self.btn_diff = ttk.Button(sec_a, text="", command=self.calc_diff)
        self.btn_diff.grid(row=1, column=3, sticky="e", pady=(6, 0))

        self.diff_out = tk.StringVar(value="—")
        ttk.Label(sec_a, textvariable=self.diff_out, font=("Segoe UI", 10)).grid(
            row=2, column=0, columnspan=4, sticky="w", pady=(10, 0)
        )


        self.h_add = ttk.Label(left, text="", font=("Segoe UI", 11, "bold"))
        self.h_add.grid(row=3, column=0, sticky="w", pady=(0, 6))

        sec_b = ttk.Frame(left, padding=10, relief="groove")
        sec_b.grid(row=4, column=0, sticky="ew", pady=(0, 18))
        for c in range(4):
            sec_b.grid_columnconfigure(c, weight=1)

        self.lbl_base = ttk.Label(sec_b, text="")
        self.lbl_base.grid(row=0, column=0, sticky="w")

        self.base = DateEntry(sec_b, date_pattern="yyyy-mm-dd")
        self.base.set_date(today)
        self.base.grid(row=0, column=1, padx=8, pady=4, sticky="w")

        self.lbl_n = ttk.Label(sec_b, text="")
        self.lbl_n.grid(row=0, column=2, sticky="w")

        self.n_days = tk.IntVar(value=0)
        self.spin_n = ttk.Spinbox(sec_b, from_=-3650, to=3650, textvariable=self.n_days, width=12)
        self.spin_n.grid(row=0, column=3, padx=8, pady=4, sticky="w")

        self.btn_add = ttk.Button(sec_b, text="", command=self.calc_add)
        self.btn_add.grid(row=1, column=3, sticky="e", pady=(6, 0))

        self.add_out = tk.StringVar(value="—")
        ttk.Label(sec_b, textvariable=self.add_out, font=("Segoe UI", 10)).grid(
            row=2, column=0, columnspan=4, sticky="w", pady=(10, 0)
        )


        self.h_week = ttk.Label(left, text="", font=("Segoe UI", 11, "bold"))
        self.h_week.grid(row=5, column=0, sticky="w", pady=(0, 6))

        sec_c = ttk.Frame(left, padding=10, relief="groove")
        sec_c.grid(row=6, column=0, sticky="ew")
        for c in range(4):
            sec_c.grid_columnconfigure(c, weight=1)

        self.lbl_year = ttk.Label(sec_c, text="")
        self.lbl_year.grid(row=0, column=0, sticky="w")

        self.week_year = tk.IntVar(value=today.year)
        self.spin_year = ttk.Spinbox(sec_c, from_=1970, to=2100, textvariable=self.week_year, width=12)
        self.spin_year.grid(row=0, column=1, padx=8, pady=4, sticky="w")

        self.lbl_week = ttk.Label(sec_c, text="")
        self.lbl_week.grid(row=0, column=2, sticky="w")

        self.week_num = tk.IntVar(value=1)
        self.spin_week = ttk.Spinbox(sec_c, from_=1, to=53, textvariable=self.week_num, width=12)
        self.spin_week.grid(row=0, column=3, padx=8, pady=4, sticky="w")

        self.btn_week = ttk.Button(sec_c, text="", command=self.calc_week_range)
        self.btn_week.grid(row=1, column=3, sticky="e", pady=(6, 0))

        self.week_out = tk.StringVar(value="—")
        ttk.Label(sec_c, textvariable=self.week_out, font=("Segoe UI", 10)).grid(
            row=2, column=0, columnspan=4, sticky="w", pady=(10, 0)
        )


        self.h_history = ttk.Label(right, text="", font=("Segoe UI", 11, "bold"))
        self.h_history.grid(row=0, column=0, sticky="w")

        list_frame = ttk.Frame(right)
        list_frame.grid(row=1, column=0, sticky="nsew", pady=6)
        list_frame.grid_rowconfigure(0, weight=1)
        list_frame.grid_columnconfigure(0, weight=1)

        self.hist_list = tk.Listbox(list_frame, height=14)
        self.hist_list.grid(row=0, column=0, sticky="nsew")

        yscroll = ttk.Scrollbar(list_frame, orient="vertical", command=self.hist_list.yview)
        yscroll.grid(row=0, column=1, sticky="ns")

        xscroll = ttk.Scrollbar(list_frame, orient="horizontal", command=self.hist_list.xview)
        xscroll.grid(row=1, column=0, sticky="ew")

        self.hist_list.configure(yscrollcommand=yscroll.set, xscrollcommand=xscroll.set)
        self.hist_list.bind("<<ListboxSelect>>", self.on_select_history)

        self.hist_details = tk.StringVar(value="")
        self.lbl_hist_details = ttk.Label(right, textvariable=self.hist_details, wraplength=420, justify="left")
        self.lbl_hist_details.grid(row=2, column=0, sticky="ew", pady=(6, 10))

        btns = ttk.Frame(right)
        btns.grid(row=3, column=0, sticky="ew")
        btns.grid_columnconfigure(0, weight=1)
        btns.grid_columnconfigure(1, weight=1)

        self.btn_copy = ttk.Button(btns, text="", command=self.copy_selected)
        self.btn_copy.grid(row=0, column=0, sticky="ew", padx=(0, 6), pady=3)

        self.btn_delete = ttk.Button(btns, text="", command=self.delete_selected)
        self.btn_delete.grid(row=0, column=1, sticky="ew", pady=3)

        self.btn_export = ttk.Button(btns, text="", command=self.export_csv)
        self.btn_export.grid(row=1, column=0, sticky="ew", padx=(0, 6), pady=3)

        self.btn_clear = ttk.Button(btns, text="", command=self.clear_history)
        self.btn_clear.grid(row=1, column=1, sticky="ew", pady=3)

    def apply_language(self):
        """Ustawia wszystkie napisy zgodnie z aktualnym językiem."""
        # combo pokazuje kody "pl/en", ale etykieta obok ma tekst
        self.lbl_language.config(text=self.tr("language"))

        # nagłówki sekcji (bold)
        self.h_diff.config(text=self.tr("section_diff"))
        self.h_add.config(text=self.tr("section_add"))
        self.h_week.config(text=self.tr("section_week"))
        self.h_history.config(text=self.tr("history"))

        # etykiety
        self.lbl_d1.config(text=self.tr("date1"))
        self.lbl_d2.config(text=self.tr("date2"))
        self.lbl_mode.config(text=self.tr("mode"))

        # radiobuttony
        self.rb_calendar.config(text=self.tr("calendar"))
        self.rb_business.config(text=self.tr("business"))


        self.btn_diff.config(text=self.tr("count"))
        self.btn_add.config(text=self.tr("count"))
        self.btn_week.config(text=self.tr("show_range"))


        self.lbl_base.config(text=self.tr("base_date"))
        self.lbl_n.config(text=self.tr("n_days"))


        self.lbl_year.config(text=self.tr("year"))
        self.lbl_week.config(text=self.tr("week"))


        self.btn_copy.config(text=self.tr("copy"))
        self.btn_delete.config(text=self.tr("delete"))
        self.btn_export.config(text=self.tr("export"))
        self.btn_clear.config(text=self.tr("clear"))


        if not self.history and (self.hist_details.get() == "" or self.hist_details.get() == self.T["pl"]["select_hint"] or self.hist_details.get() == self.T["en"]["select_hint"]):
            self.hist_details.set(self.tr("select_hint"))


        sel = self.hist_list.curselection()
        if sel:
            self.show_details_for_index(sel[0])


    def calc_diff(self):
        d1 = self.d1.get_date()
        d2 = self.d2.get_date()

        if self.mode.get() == "robocze":
            delta_days = self.business_days_between(d1, d2)
        else:
            delta_days = (d2 - d1).days

        weeks, rest = weeks_and_days(delta_days)
        self.diff_out.set(self.tr("diff_result").format(days=delta_days, weeks=weeks, rest=rest))

        self.add_history_item({
            "type": "diff",
            "d1": str(d1),
            "d2": str(d2),
            "delta_days": delta_days,
            "weeks": weeks,
            "rem_days": rest,
        })

    def calc_add(self):
        base_date = self.base.get_date()
        n = int(self.n_days.get())

        target = base_date + timedelta(days=n)


        self.add_out.set(self.tr("add_result").format(target=str(target)))

        self.add_history_item({
            "type": "add",
            "base": str(base_date),
            "n": n,
            "target": str(target),
        })

    def calc_week_range(self):
        y = int(self.week_year.get())
        w = int(self.week_num.get())

        try:
            monday = date.fromisocalendar(y, w, 1)
            sunday = monday + timedelta(days=6)
        except ValueError:
            messagebox.showerror(self.tr("err_title"), self.tr("err_bad_week"))
            return

        if self.lang.get() == "pl":
            pretty = format_range_pl(monday, sunday)
        else:
            pretty = format_range_en(monday, sunday)

        self.week_out.set(self.tr("week_result").format(w=w, y=y, start=str(monday), end=str(sunday), pretty=pretty))

        self.add_history_item({
            "type": "week",
            "year": y,
            "week": w,
            "start": str(monday),
            "end": str(sunday),
        })


    def add_history_item(self, item: dict):
        self.history.append(item)


        if item["type"] == "diff":
            line = f"Δ {item['delta_days']}d | {item['d1']} → {item['d2']}"
        elif item["type"] == "add":
            n = item["n"]
            sign = "+" if n >= 0 else ""
            line = f"{sign}{n}d | {item['base']} → {item['target']}"
        else:
            line = f"Week {item['week']} ({item['year']}) | {item['start']} → {item['end']}"

        self.hist_list.insert(tk.END, line)

        self.hist_list.selection_clear(0, tk.END)
        self.hist_list.selection_set(tk.END)
        self.hist_list.see(tk.END)

        self.show_details_for_index(len(self.history) - 1)

    def on_select_history(self, _event=None):
        selected = self.hist_list.curselection()
        if not selected:
            return
        self.show_details_for_index(selected[0])

    def show_details_for_index(self, idx: int):
        item = self.history[idx]

        if item["type"] == "diff":
            text = (
                f"{self.tr('type_diff')}\n"
                f"{self.tr('date1')} {item['d1']}\n"
                f"{self.tr('date2')} {item['d2']}\n"
                f"{self.tr('diff_result').format(days=item['delta_days'], weeks=item['weeks'], rest=item['rem_days'])}"
            )
        elif item["type"] == "add":
            text = (
                f"{self.tr('type_add')}\n"
                f"{self.tr('base_date')} {item['base']}\n"
                f"{self.tr('n_days')} {item['n']}\n"
                f"{self.tr('add_result').format(target=item['target'])}"
            )
        else:
            if self.lang.get() == "pl":
                pretty = format_range_pl(date.fromisoformat(item["start"]), date.fromisoformat(item["end"]))
            else:
                pretty = format_range_en(date.fromisoformat(item["start"]), date.fromisoformat(item["end"]))

            text = (
                f"{self.tr('type_week')}\n"
                f"{self.tr('week')} {item['week']} / {self.tr('year')} {item['year']}\n"
                f"{item['start']} – {item['end']}\n"
                f"{pretty}"
            )

        self.hist_details.set(text)


    def copy_selected(self):
        selected = self.hist_list.curselection()
        if not selected:
            messagebox.showinfo(self.tr("info_title"), self.tr("info_no_selection"))
            return

        line = self.hist_list.get(selected[0])
        self.clipboard_clear()
        self.clipboard_append(line)

    def delete_selected(self):
        selected = self.hist_list.curselection()
        if not selected:
            return

        idx = selected[0]
        self.hist_list.delete(idx)
        self.history.pop(idx)

        self.hist_details.set(self.tr("deleted"))

        if self.history:
            new_idx = min(idx, len(self.history) - 1)
            self.hist_list.selection_set(new_idx)
            self.show_details_for_index(new_idx)

    def clear_history(self):
        self.history.clear()
        self.hist_list.delete(0, tk.END)
        self.hist_details.set(self.tr("cleared"))

    def export_csv(self):
        if not self.history:
            messagebox.showinfo(self.tr("info_title"), self.tr("info_empty_history"))
            return

        path = filedialog.asksaveasfilename(
            defaultextension=".csv",
            filetypes=[("CSV", "*.csv")]
        )
        if not path:
            return

        all_keys = set()
        for item in self.history:
            for k in item.keys():
                all_keys.add(k)

        fieldnames = sorted(all_keys)

        with open(path, "w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            for item in self.history:
                writer.writerow(item)

        messagebox.showinfo(self.tr("ok_title"), self.tr("ok_exported").format(path=path))


if __name__ == "__main__":
    app = PlannerApp()
    app.mainloop()