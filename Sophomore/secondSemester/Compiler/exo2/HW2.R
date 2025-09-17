# Read and clean data
fees <- utils::read.csv("HW2-Fees.csv") |>
  dplyr::mutate(Amount = base::as.numeric(base::gsub(",", "", base::trimws(Amount))))

student_main <- utils::read.csv("HW2-Student-Main.csv")

payments <- utils::read.csv("HW2-Student-Payment.csv") |>
  dplyr::mutate(Amount = base::as.numeric(base::gsub(",", "", base::trimws(Amount))))

# Merge all tables and calculate metrics
student_financial_status <- student_main |>
  dplyr::left_join(fees, by = "Payment.Type") |>
  dplyr::left_join(payments, by = "Student.ID", suffix = c("_required", "_paid")) |>
  dplyr::mutate(
    Amount_paid = dplyr::coalesce(Amount_paid, 0),
    Shortage = Amount_required - Amount_paid
  )

# Computation #1: Total paid
total_paid <- base::sum(student_financial_status$Amount_paid)
base::cat("Total Payment Received:", base::format(total_paid, big.mark = ",", nsmall = 2), "\n\n")

# Computation #2: Students with shortage
students_with_shortage <- student_financial_status |>
  dplyr::filter(Shortage > 0) |>
  dplyr::select(Student.ID, Name,
    Fee_Required = Amount_required,
    Amount_Paid = Amount_paid,
    Shortage
  ) |>
  dplyr::mutate(
    Fee_Required = base::formatC(Fee_Required, format = "f", big.mark = ",", digits = 2),
    Amount_Paid  = base::formatC(Amount_Paid, format = "f", big.mark = ",", digits = 2),
    Shortage     = base::formatC(Shortage, format = "f", big.mark = ",", digits = 2)
  )

base::cat("Students with Shortage:\n")
base::print(students_with_shortage, row.names = FALSE, right = FALSE)
