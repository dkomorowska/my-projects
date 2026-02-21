# Lead Time Planner - Date Calculator

Lead Time Planner is a lightweight desktop application built with
**Python (Tkinter)** for calculating date-based operations in a simple
and user-friendly interface.

The application supports both **English and Polish language modes**.

------------------------------------------------------------------------

## 📌 Features

### 1️⃣ Date Difference

-   Select **Date 1** and **Date 2**
-   Choose calculation mode:
    -   Calendar days
    -   Business days (Monday--Friday)
-   Result displays:
    -   Total number of days
    -   Equivalent number of weeks and remaining days

------------------------------------------------------------------------

### 2️⃣ Date + N Days

-   Select a base date
-   Enter a positive or negative number of days
-   The application calculates the resulting date

------------------------------------------------------------------------

### 3️⃣ Week → Date Range

-   Select ISO **Year** and **Week number**
-   The application returns:
    -   Monday and Sunday of the selected week
    -   A formatted human-readable date range

------------------------------------------------------------------------

### 4️⃣ History Panel

All calculations are automatically saved in the History section.

Available actions: - Copy selected - Delete selected - Export to CSV -
Clear history

The CSV export includes all calculation types with dynamically generated
columns.

------------------------------------------------------------------------

## 🌍 Language Support

The application includes a language switcher: - English - Polish

All labels, buttons, messages, and history descriptions update
dynamically.

------------------------------------------------------------------------


## 📁 Project Structure (example)

    project-folder/
    │
    ├── planner.py
    ├── README.md
    └── screenshot.png

------------------------------------------------------------------------

## 🧠 Technical Notes

-   Built using `tkinter` and `ttk`
-   ISO week calculations use Python's `datetime.fromisocalendar`
-   Business day calculation excludes weekends (Mon--Fri logic)
-   CSV export dynamically adjusts to different history entry types

------------------------------------------------------------------------

## 📄 License

This project is provided for educational and personal use.

------------------------------------------------------------------------

## 👩‍💻 Author

Dominika Komorowska
