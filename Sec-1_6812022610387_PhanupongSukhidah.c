#include <stdio.h>

// Function declarations
float getHourlyRate(char level);
float calculateTotalOT(float othours[], int days);
float calculateDeductionRate(char level);
float calculateNetIncome(float gross, float deductionRate);

int main() {
    int days;
    float othours[10];
    char incomeLevel;
    float total_ot, hourly_rate, gross_income, net_income, deductionRate;

    printf("*** OT and Tax Calculator ***\n");

    // รับค่าการทำ OT
    do {
        printf("Enter number of OT days (1-10): ");
        scanf("%d", &days);
    } while (days < 1 || days > 10);

    for (int i = 0; i < days; i++) {
        printf("Enter OT Hours for day %d: ", i + 1);
        scanf("%f", &othours[i]);
        if (i < days - 1) printf("...(input continue)...\n");
    }

    // ล้าง buffer ก่อนรับตัวอักษร
    while (getchar() != '\n');

    printf("Enter Income Level (L,M,H): ");
    scanf("%c", &incomeLevel);

    hourly_rate = getHourlyRate(incomeLevel);
    total_ot = calculateTotalOT(othours, days);
    gross_income = hourly_rate * total_ot;
    deductionRate = calculateDeductionRate(incomeLevel);
    net_income = calculateNetIncome(gross_income, deductionRate);

    // แสดงผล
    printf("\n--- Income Summary ---\n");
    switch (incomeLevel) {
        case 'L': case 'l':
            printf("Income Level: Low (75 THB/hr)\n");
            break;
        case 'M': case 'm':
            printf("Income Level: Medium (120 THB/hr)\n");
            break;
        case 'H': case 'h':
            printf("Income Level: High (180 THB/hr)\n");
            break;
        default:
            printf("Income Level: Unknown\n");
            break;
    }

    printf("OT Hours Recorded (%d): ", days);
    for (int i = 0; i < days; i++) {
        printf("%.2f", othours[i]);
        if (i < days - 1) printf(", ");
    }
    printf("\n");

    printf("Total OT Hours: %.2f hrs\n", total_ot);
    printf("Total Gross Income: %.2f THB\n", gross_income);
    printf("Deduction Rate: %.2f%%\n", deductionRate * 100);
    printf("Net Income: %.2f THB\n", net_income);

    return 0;
}

// Rate ตามระดับรายได้
float getHourlyRate(char level) {
    switch (level) {
        case 'L': case 'l': return 75.0;
        case 'M': case 'm': return 120.0;
        case 'H': case 'h': return 180.0;
        default: return 0.0;
    }
}

// รวมชั่วโมง OT
float calculateTotalOT(float othours[], int days) {
    float total = 0.0;
    for (int i = 0; i < days; i++) {
        total += othours[i];
    }
    return total;
}

// อัตราการหักภาษี
float calculateDeductionRate(char level) {
    switch (level) {
        case 'L': case 'l': return 0.10;
        case 'M': case 'm': return 0.15;
        case 'H': case 'h': return 0.20;
        default: return 0.10;
    }
}

// คำนวณรายได้สุทธิ
float calculateNetIncome(float gross, float deductionRate) {
    return gross * (1 - deductionRate);
}
