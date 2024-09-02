#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(void)
{
	//Relevant Arrays
	char GEO[300][50];
	char Age_group[300][50];
	char Sex[300][50];
	char Value[300][50];

	double Value_Conv[300];

	char line[2000];
	char REF_DATE[1000][1000];

	//Necessary Pointers
	FILE * fp;
	char *sp;	//Used as a way to grab the individual data entries

	//Line variables
	int REF_lines = 0;
	int GEO_lines = 0;
	int AG_lines = 0;
	int SEX_lines = 0;
	int VAL_lines = 0;
	int value_index = 0;
	int line_count = 0;

	//# of data entries
	int data = 210;

	fp = fopen("statscan_diabetes.txt", "r");

	if (fp == NULL)
	{
		printf("Error: could not open file\n");
		return 1;
	}

	//Read and Grab all the Relevant Data from the .csv File (line_count to prevent truncating, 210 is # of data entries present in csv)
	while (fgets(line, 2000, fp) != NULL && line_count < data)
	{
		//Ignore the header columns
		if (strstr(line, "REF_DATE") != NULL)
		{
			continue;
		}

		//GRAB THE REF_DATES
		sp = strtok(line, ",\"");	//take a look at the line and start at the beginning, and stop when it sees a comma or quotation marks as it sees them as delimiters so the function will ignore the quotation marks and treat the data inside as a single entity.
		strcpy(REF_DATE[REF_lines], sp);
		REF_lines++;

		//GRAB THE GEO LOCATIONS
		sp = strtok(NULL, ",\"");	//pick up where you left off, after the next comma and grab that chunk of data
		strcpy(GEO[GEO_lines], sp);
		GEO_lines++;

		//SKIP
		sp = strtok(NULL, ",");

		//GRAB AGE 
		sp = strtok(NULL, ",\"");
		strcpy(Age_group[AG_lines], sp);
		AG_lines++;

		//GRAB SEX
		sp = strtok(NULL, ",\"");
		strcpy(Sex[SEX_lines], sp);
		SEX_lines++;

		// Skip irrelevant columns
		for (int i = 0; i < 8; i++)
		{
			sp = strtok(NULL, ",");
		}

		//GRAB Value
		sp = strtok(NULL, ",\"");
		strcpy(Value[VAL_lines], sp);
		VAL_lines++;
		line_count++;
	}

	fclose(fp);

	//Convert String Values from 'Value' to Double Values, Place to 'Value_Conv'
	int i = 0, j = 0;

	for (i = 0; i < VAL_lines; i++)
	{
		Value_Conv[j] = atof(Value[i]);	// convert string to double
		j++;
	}

	//QUESTION #1 (a): Averages of the percentage of the population that are diagnosed with diabetes[PROVINCIAL AVERAGES]. 

	//Necessary Variables needed to Compute
	double ontario_total = 0.0, quebec_total = 0.0, bc_total = 0.0, alberta_total = 0.0;
	int ontario_count = 0, quebec_count = 0, bc_count = 0, alberta_count = 0;

	// Calculate Provincial Averages
	for (int i = 0; i < VAL_lines; i++)
	{
		if (strcmp(GEO[i], "Ontario") == 0)
		{
			if (strcmp(Value[i], "F") != 0)
			{
				ontario_total += Value_Conv[i];
				ontario_count++;
			}
		}
		else if (strcmp(GEO[i], "British Columbia") == 0)
		{
			if (strcmp(Value[i], "F") != 0)
			{
				bc_total += Value_Conv[i];
				bc_count++;
			}
		}
		else if (strcmp(GEO[i], "Quebec") == 0)
		{
			if (strcmp(Value[i], "F") != 0)
			{
				quebec_total += Value_Conv[i];
				quebec_count++;
			}
		}
		else if (strcmp(GEO[i], "Alberta") == 0)
		{
			if (strcmp(Value[i], "F") != 0)
			{
				alberta_total += Value_Conv[i];
				alberta_count++;
			}
		}
	}

	//Calculate Individual Province Averages Based on Count
	double p_ontario_avg = ontario_total / ontario_count;
	double p_quebec_avg = quebec_total / quebec_count;
	double p_bc_avg = bc_total / bc_count;
	double p_alberta_avg = alberta_total / alberta_count;

	// Output Provincial Averages
	printf("\n");
	printf("#1 a) \n");
	printf("---------------------------\n");
	printf("Provincial Averages:\n");
	printf("Ontario: %.2f%%\n", p_ontario_avg);
	printf("Quebec: %.2f%%\n", p_quebec_avg);
	printf("British Columbia: %.2f%%\n", p_bc_avg);
	printf("Alberta: %.2f%%\n", p_alberta_avg);
	printf("---------------------------\n");
	printf("\n");

	//QUESTION #1 (b): Averages of the percentage of the population that are diagnosed with diabetes[NATIONAL AVERAGE]. 

	//Necessary Variables needed to Compute
	double national_sum = 0.0;
	int national_count = 0;

	// Calculate National Average
	for (int i = 0; i < VAL_lines; i++)
	{
		if (strcmp(GEO[i], "Canada (excluding territories)") == 0)
		{
			if (strcmp(Value[i], "F") != 0)
			{
				national_sum += Value_Conv[i];
				national_count++;
			}
		}
	}

	//Print out National Average
	double p_national_avg = national_sum / national_count;
	printf("#1 b) \n");
	printf("---------------------------\n");
	printf("National Average: %.2f%%\n", p_national_avg);
	printf("---------------------------\n");
	printf("\n");

	//QUESTION #1 (c): Yearly Averages, Average Per Year for each Province and Whole Country. 

	//Necessary Variables needed to Compute

	//row = # of years
	double ontario_yearly_totals[7] = { 0.0 };

	int ontario_yearly_counts[7] = { 0 };

	double quebec_yearly_totals[7] = { 0.0 };

	int quebec_yearly_counts[7] = { 0 };

	double bc_yearly_totals[7] = { 0.0 };

	int bc_yearly_counts[7] = { 0 };

	double alberta_yearly_totals[7] = { 0.0 };

	int alberta_yearly_counts[7] = { 0 };

	double national_yearly_totals[7] = { 0.0 };

	int national_yearly_counts[7] = { 0 };

	double yearly_totals[7] = { 0.0 };

	int yearly_counts[7] = { 0 };

	//Variables for compute
	int counter = 0;
	double yearly_avg, national_avg, alberta_avg, ontario_avg, quebec_avg,
	bc_avg;

	//Cycles through each of the years to calculate averages
	for (int year = 2015; year <= 2021; year++)
	{
		//Converts the year to a string to be compared to for each year 
		char year_str[5];
		sprintf(year_str, "%d", year);
		int index = year - 2015;

		for (int i = 0; i < VAL_lines; i++)
		{
			// Calculate Yearly Average in the current year, and National &Province Averages in the current year
			if (strcmp(REF_DATE[i], year_str) == 0 && strcmp(Value[i], "F") != 0)
			{
				if (strcmp(GEO[i], "Alberta") == 0)
				{
					alberta_yearly_totals[index] += Value_Conv[i];
					alberta_yearly_counts[index]++;
				}

				if (strcmp(GEO[i], "Ontario") == 0)
				{
					ontario_yearly_totals[index] += Value_Conv[i];
					ontario_yearly_counts[index]++;
				}

				if (strcmp(GEO[i], "Quebec") == 0)
				{
					quebec_yearly_totals[index] += Value_Conv[i];
					quebec_yearly_counts[index]++;
				}

				if (strcmp(GEO[i], "British Columbia") == 0)
				{
					bc_yearly_totals[index] += Value_Conv[i];
					bc_yearly_counts[index]++;
				}

				if (strcmp(GEO[i], "Canada (excluding territories)") == 0)
				{
					national_yearly_totals[index] += Value_Conv[i];
					national_yearly_counts[index]++;
				}

				yearly_totals[index] += Value_Conv[i];
				yearly_counts[index]++;
			}
		}
	}

	//Print out the results
	//Print out results[TABLE]
	printf("#1 c) \n");
	printf("------------------------------------------------------------------------------------ \n");
	printf("\t   Number of People (All Ages) that have Diabetes in Canada (in %%)\n");
	printf("------------------------------------------------------------------------------------ \n");
	printf("Province:   |2015|     |2016|     |2017|     |2018|     |2019|     |2020|     |2021|\n");

	//Print out results for each province
	printf("   AB ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", alberta_yearly_totals[i] / alberta_yearly_counts[i]);
	}

	printf("\n");

	printf("   BC ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", bc_yearly_totals[i] / bc_yearly_counts[i]);
	}

	printf("\n");

	printf("   ON ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", ontario_yearly_totals[i] / ontario_yearly_counts[i]);
	}

	printf("\n");

	printf("   QC ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", quebec_yearly_totals[i] / quebec_yearly_counts[i]);
	}

	printf("\n");

	printf("   CA ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", national_yearly_totals[i] / national_yearly_counts[i]);
	}

	printf("\n");

	//Print out yearly Averages
	printf("------------------------------------------------------------------------------------ \n");
	printf(" Y. Avg");
	for (int i = 0; i < 7; i++)
	{
		printf("     %.2lf ", yearly_totals[i] / yearly_counts[i]);
	}

	printf("\n");
	printf("------------------------------------------------------------------------------------ \n");

	//QUESTION #1 (c): The avg % of diabetes among age groups (35-49, 60-64, 65+). One average per age group (all years) for each province and the whole country.

	//rows = age groups, col = year#
	double ontario_age_group_totals[3][7] = { 0.0 };

	int ontario_age_group_counts[3][7] = { 0 };

	double quebec_age_group_totals[3][7] = { 0.0 };

	int quebec_age_group_counts[3][7] = { 0 };

	double bc_age_group_totals[3][7] = { 0.0 };

	int bc_age_group_counts[3][7] = { 0 };

	double alberta_age_group_totals[3][7] = { 0.0 };

	int alberta_age_group_counts[3][7] = { 0 };

	double national_age_group_totals[3][7] = { 0.0 };

	int national_age_group_counts[3][7] = { 0 };

	//Row = province, col = age groups
	double yearly_age_totals[5][3] = { 0 };

	int yearly_age_counts[5][3] = { 0 };

	for (int year = 2015; year <= 2021; year++)
	{
		char year_str[5];
		sprintf(year_str, "%d", year);
		int index = year - 2015;

		for (int i = 0; i < VAL_lines; i++)
		{
			if (strcmp(REF_DATE[i], year_str) == 0 && strcmp(Value[i], "F") != 0)
			{
				int age_group = -1;
				//If statements to seperate the Age Groups
				if (strcmp(Age_group[i], "35 to 49 years") == 0)
				{
					age_group = 0;
				}
				else if (strcmp(Age_group[i], "50 to 64 years") == 0)
				{
					age_group = 1;
				}
				else if (strcmp(Age_group[i], "65 years and over") == 0)
				{
					age_group = 2;
				}

				//Split the Averages 
				if (age_group == 0)	//35-49
				{
					if (strcmp(GEO[i], "Alberta") == 0)
					{
						alberta_age_group_totals[0][index] += Value_Conv[i];
						alberta_age_group_counts[0][index]++;
						yearly_age_totals[0][0] += Value_Conv[i];
						yearly_age_counts[0][0]++;
					}

					if (strcmp(GEO[i], "Ontario") == 0)
					{
						ontario_age_group_totals[0][index] += Value_Conv[i];
						ontario_age_group_counts[0][index]++;
						yearly_age_totals[1][0] += Value_Conv[i];
						yearly_age_counts[1][0]++;
					}

					if (strcmp(GEO[i], "Quebec") == 0)
					{
						quebec_age_group_totals[0][index] += Value_Conv[i];
						quebec_age_group_counts[0][index]++;
						yearly_age_totals[2][0] += Value_Conv[i];
						yearly_age_counts[2][0]++;
					}

					if (strcmp(GEO[i], "British Columbia") == 0)
					{
						bc_age_group_totals[0][index] += Value_Conv[i];
						bc_age_group_counts[0][index]++;
						yearly_age_totals[3][0] += Value_Conv[i];
						yearly_age_counts[3][0]++;
					}

					if (strcmp(GEO[i], "Canada (excluding territories)") == 0)
					{
						national_age_group_totals[0][index] += Value_Conv[i];
						national_age_group_counts[0][index]++;
						yearly_age_totals[4][0] += Value_Conv[i];
						yearly_age_counts[4][0]++;
					}
				}

				//Split the Averages 
				if (age_group == 1)	//50-64
				{
					if (strcmp(GEO[i], "Alberta") == 0)
					{
						alberta_age_group_totals[1][index] += Value_Conv[i];
						alberta_age_group_counts[1][index]++;
						yearly_age_totals[0][1] += Value_Conv[i];
						yearly_age_counts[0][1]++;
					}

					if (strcmp(GEO[i], "Ontario") == 0)
					{
						ontario_age_group_totals[1][index] += Value_Conv[i];
						ontario_age_group_counts[1][index]++;
						yearly_age_totals[1][1] += Value_Conv[i];
						yearly_age_counts[1][1]++;
					}

					if (strcmp(GEO[i], "Quebec") == 0)
					{
						quebec_age_group_totals[1][index] += Value_Conv[i];
						quebec_age_group_counts[1][index]++;
						yearly_age_totals[2][1] += Value_Conv[i];
						yearly_age_counts[2][1]++;
					}

					if (strcmp(GEO[i], "British Columbia") == 0)
					{
						bc_age_group_totals[1][index] += Value_Conv[i];
						bc_age_group_counts[1][index]++;
						yearly_age_totals[3][1] += Value_Conv[i];
						yearly_age_counts[3][1]++;
					}

					if (strcmp(GEO[i], "Canada (excluding territories)") == 0)
					{
						national_age_group_totals[1][index] += Value_Conv[i];
						national_age_group_counts[1][index]++;
						yearly_age_totals[4][1] += Value_Conv[i];
						yearly_age_counts[4][1]++;
					}
				}

				//Split the Averages 
				if (age_group == 2)	//65+
				{
					if (strcmp(GEO[i], "Alberta") == 0)
					{
						alberta_age_group_totals[2][index] += Value_Conv[i];
						alberta_age_group_counts[2][index]++;
						yearly_age_totals[0][2] += Value_Conv[i];
						yearly_age_counts[0][2]++;
					}

					if (strcmp(GEO[i], "Ontario") == 0)
					{
						ontario_age_group_totals[2][index] += Value_Conv[i];
						ontario_age_group_counts[2][index]++;
						yearly_age_totals[1][2] += Value_Conv[i];
						yearly_age_counts[1][2]++;
					}

					if (strcmp(GEO[i], "Quebec") == 0)
					{
						quebec_age_group_totals[2][index] += Value_Conv[i];
						quebec_age_group_counts[2][index]++;
						yearly_age_totals[2][2] += Value_Conv[i];
						yearly_age_counts[2][2]++;
					}

					if (strcmp(GEO[i], "British Columbia") == 0)
					{
						bc_age_group_totals[2][index] += Value_Conv[i];
						bc_age_group_counts[2][index]++;
						yearly_age_totals[3][2] += Value_Conv[i];
						yearly_age_counts[3][2]++;
					}

					if (strcmp(GEO[i], "Canada (excluding territories)") == 0)
					{
						national_age_group_totals[2][index] += Value_Conv[i];
						national_age_group_counts[2][index]++;
						yearly_age_totals[4][2] += Value_Conv[i];
						yearly_age_counts[4][2]++;
					}
				}
			}
		}
	}

	printf("\n");
	printf("#1 d)\n");

	//Print out the results
	//Print out results[ONTARIO]
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\t\t\tNumber of People that have Diabetes in Ontario (in %%)\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("Age Group:    |2015|     |2016|     |2017|     |2018|     |2019|     |2020|     |2021|      |Average|\n");

	//Print out results for each province
	printf("  35-49 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", ontario_age_group_totals[0][i] / ontario_age_group_counts[0][i]);
	}

	printf("%13.2lf", yearly_age_totals[1][0] / yearly_age_counts[1][0]);	//Print out yearly average
	printf("\n");

	printf("  50-64 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", ontario_age_group_totals[1][i] / ontario_age_group_counts[1][i]);
	}

	printf("%13.2lf", yearly_age_totals[1][1] / yearly_age_counts[1][1]);	//Print out yearly average
	printf("\n");

	printf("    65+ ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", ontario_age_group_totals[2][i] / ontario_age_group_counts[2][i]);
	}

	printf("%13.2lf", yearly_age_totals[1][2] / yearly_age_counts[1][2]);	//Print out yearly average
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\n");

	//Print out the results
	//Print out results[ALBERTA]
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\t\t\tNumber of People that have Diabetes in Alberta (in %%)\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("Age Group:    |2015|     |2016|     |2017|     |2018|     |2019|     |2020|     |2021|      |Average|\n");

	//Print out results for each province
	printf("  35-49 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", alberta_age_group_totals[0][i] / alberta_age_group_counts[0][i]);
	}

	printf("%13.2lf", yearly_age_totals[0][0] / yearly_age_counts[0][0]);	//Print out yearly average
	printf("\n");

	printf("  50-64 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", alberta_age_group_totals[1][i] / alberta_age_group_counts[1][i]);
	}

	printf("%13.2lf", yearly_age_totals[0][1] / yearly_age_counts[0][1]);	//Print out yearly average
	printf("\n");

	printf("    65+ ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", alberta_age_group_totals[2][i] / alberta_age_group_counts[2][i]);
	}

	printf("%13.2lf", yearly_age_totals[0][2] / yearly_age_counts[0][2]);	//Print out yearly average
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\n");

	//Print out the results
	//Print out results[QUEBEC]
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\t\t\tNumber of People that have Diabetes in Quebec (in %%)\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("Age Group:    |2015|     |2016|     |2017|     |2018|     |2019|     |2020|     |2021|      |Average|\n");

	//Print out results for each province
	printf("  35-49 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", quebec_age_group_totals[0][i] / quebec_age_group_counts[0][i]);
	}

	printf("%13.2lf", yearly_age_totals[2][0] / yearly_age_counts[2][0]);	//Print out yearly average
	printf("\n");

	printf("  50-64 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", quebec_age_group_totals[1][i] / quebec_age_group_counts[1][i]);
	}

	printf("%13.2lf", yearly_age_totals[2][1] / yearly_age_counts[2][1]);	//Print out yearly average
	printf("\n");

	printf("    65+ ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", quebec_age_group_totals[2][i] / quebec_age_group_counts[2][i]);
	}

	printf("%13.2lf", yearly_age_totals[2][2] / yearly_age_counts[2][2]);	//Print out yearly average
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\n");

	//Print out results[BC]
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\t\t\tNumber of People that have Diabetes in B.C (in %%)\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("Age Group:    |2015|     |2016|     |2017|     |2018|     |2019|     |2020|     |2021|      |Average|\n");

	//Print out results for each province
	printf("  35-49 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", bc_age_group_totals[0][i] / bc_age_group_counts[0][i]);
	}

	printf("%13.2lf", yearly_age_totals[3][0] / yearly_age_counts[3][0]);	//Print out yearly average
	printf("\n");

	printf("  50-64 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", bc_age_group_totals[1][i] / bc_age_group_counts[1][i]);
	}

	printf("%13.2lf", yearly_age_totals[3][1] / yearly_age_counts[3][1]);	//Print out yearly average
	printf("\n");

	printf("    65+ ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", bc_age_group_totals[2][i] / bc_age_group_counts[2][i]);
	}

	printf("%13.2lf", yearly_age_totals[3][2] / yearly_age_counts[3][2]);	//Print out yearly average
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\n");

	//Print out the results
	//Print out results[NATIONAL]
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\t  Number of People that have Diabetes in Canada (Excluding Territories) (in %%)\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("Age Group:    |2015|     |2016|     |2017|     |2018|     |2019|     |2020|     |2021|      |Average|\n");

	//Print out results for each province
	printf("  35-49 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", national_age_group_totals[0][i] / national_age_group_counts[0][i]);
	}

	printf("%13.2lf", yearly_age_totals[4][0] / yearly_age_counts[4][0]);	//Print out yearly average
	printf("\n");

	printf("  50-64 ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", national_age_group_totals[1][i] / national_age_group_counts[1][i]);
	}

	printf("%13.2lf", yearly_age_totals[4][1] / yearly_age_counts[4][1]);	//Print out yearly average
	printf("\n");

	printf("    65+ ");
	for (int i = 0; i < 7; i++)
	{
		printf("%11.2lf", national_age_group_totals[2][i] / national_age_group_counts[2][i]);
	}

	printf("%13.2lf", yearly_age_totals[4][2] / yearly_age_counts[4][2]);	//Print out yearly average
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------- \n");
	printf("\n");

	//#2 Province that has highest percentage of diabetes and which province has the lowest percentage.
	printf("#2\n");
	double province_avgs[4] = { 0.0 };

	char *province_names[5] = { "Ontario", "Quebec", "British Columbia", "Alberta" };

	province_avgs[0] = p_ontario_avg;
	province_avgs[1] = p_quebec_avg;
	province_avgs[2] = p_bc_avg;
	province_avgs[3] = p_alberta_avg;

	int province_avgs_size = sizeof(province_avgs) / sizeof(province_avgs[0]);
	int max = 0, min = 0;
	for (int i = 1; i < province_avgs_size; i++)
	{
		if (province_avgs[i] < province_avgs[min])
		{
			min = i;
		}

		if (province_avgs[i] > province_avgs[max])
		{
			max = i;
		}
	}

	printf("------------------------------------------------------------------------\n");
	printf("➪ Province that has Highest %% of Diabetes is %s with %.2lf%% \n", province_names[max], province_avgs[max]);
	printf("➪ Province that has Lowest %% of Diabetes is %s with %.2lf%% \n", province_names[min], province_avgs[min]);
	printf("------------------------------------------------------------------------\n");
	printf("\n");

	//#3 Provinces that have diabetes percentages above/below the national average
	printf("#3\n");
	printf("------------------------------------------------------------------------\n");

	// Compare each province's diabetes percentage to the national average
	for (int i = 0; i < province_avgs_size; i++)
	{
		if (province_avgs[i] > p_national_avg)
		{
			printf("➪ %s has diabetes percentage above the national average\n", province_names[i]);
			printf("------------------------------------------------------------------------\n");
		}
		else
		{
			printf("➪ %s has diabetes percentage below the national average\n", province_names[i]);
		}
	}

	printf("------------------------------------------------------------------------\n");

	//#4 Year and Province that has the Highest/Lowest % of Diabetes

	// Determine year with highest diabetes rate
	double max_yearly_avg = -1.0;	//set max_yearly_avg to a negative number so it can be properly compared
	int max_year = -1;

	for (int i = 0; i < 7; i++)
	{
		yearly_avg = yearly_totals[i] / yearly_counts[i];
		if (yearly_avg > max_yearly_avg)
		{
			max_yearly_avg = yearly_avg;
			max_year = i + 2015;
		}
	}

	// Determine province with highest diabetes rate
	double max_province_avg = -1.0;
	char *max_province;

	//Tallys the total to then average out
	for (int i = 0; i < 7; i++)
	{
		alberta_avg += alberta_yearly_totals[i] / alberta_yearly_counts[i];
		ontario_avg += ontario_yearly_totals[i] / ontario_yearly_counts[i];
		quebec_avg += quebec_yearly_totals[i] / quebec_yearly_counts[i];
		bc_avg += bc_yearly_totals[i] / bc_yearly_counts[i];

		//Average of each province
		alberta_avg /= 7;
		ontario_avg /= 7;
		quebec_avg /= 7;
		bc_avg /= 7;

		if (alberta_avg > max_province_avg)
		{
			max_province_avg = alberta_avg;
			max_province = "Alberta";
		}

		if (ontario_avg > max_province_avg)
		{
			max_province_avg = ontario_avg;
			max_province = "Ontario";
		}

		if (quebec_avg > max_province_avg)
		{
			max_province_avg = quebec_avg;
			max_province = "Quebec";
		}

		if (bc_avg > max_province_avg)
		{
			max_province_avg = bc_avg;
			max_province = "British Columbia";
		}
	}

	printf("\n");
	printf("#4 \n");
	printf("------------------------------------------------------------------------\n");
	printf("➪ Province with highest diabetes rate: %s\n", max_province);
	printf("➪ Year with highest diabetes rate: %d\n", max_year);
	printf("------------------------------------------------------------------------\n");

	// Determine year with lowest diabetes rate
	double min_yearly_avg = 50.0;	//Set min_yearly_avg to a high value so it can the compared correctly
	int min_year = -1;

	for (int i = 0; i < 7; i++)
	{
		yearly_avg = yearly_totals[i] / yearly_counts[i];
		if (yearly_avg < min_yearly_avg)
		{
			min_yearly_avg = yearly_avg;
			min_year = i + 2015;
		}
	}

	// Determine province with lowest diabetes rate
	double min_province_avg = 50.0;
	char *min_province;

	//Tallys the total to then average out
	for (int i = 0; i < 7; i++)
	{
		alberta_avg += alberta_yearly_totals[i] / alberta_yearly_counts[i];
		ontario_avg += ontario_yearly_totals[i] / ontario_yearly_counts[i];
		quebec_avg += quebec_yearly_totals[i] / quebec_yearly_counts[i];
		bc_avg += bc_yearly_totals[i] / bc_yearly_counts[i];

		//Averages of each Province
		alberta_avg /= 7;
		ontario_avg /= 7;
		quebec_avg /= 7;
		bc_avg /= 7;

		if (alberta_avg < min_province_avg)
		{
			min_province_avg = alberta_avg;
			min_province = "Alberta";
		}

		if (ontario_avg < min_province_avg)
		{
			min_province_avg = ontario_avg;
			min_province = "Ontario";
		}

		if (quebec_avg < min_province_avg)
		{
			min_province_avg = quebec_avg;
			min_province = "Quebec";
		}

		if (bc_avg < min_province_avg)
		{
			min_province_avg = bc_avg;
			min_province = "British Columbia";
		}
	}

	printf("------------------------------------------------------------------------\n");
	printf("➪ Province with lowest diabetes rate: %s\n", min_province);
	printf("➪ Year with lowest diabetes rate: %d\n", min_year);
	printf("------------------------------------------------------------------------\n");
	printf("\n");

	return 0;
}