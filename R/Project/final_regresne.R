# In the period 1962-77, 205 patients with malignant melanoma (cancer of
#                                                              the skin) had a radical operation performed at Odense University
# Hospital, Denmark. All patients were followed until the end of 1977 by 
# which time 134 were still alive while 71 had died (of out whom 57 had
# died from cancer and 14 from other causes).
# 
# The object of the study was to assess the effect of risk factors on
# survival. Among such risk factors were the sex and age of the patients
# and the histological variables tumor thickness and ulceration (absent
# vs. present).
# 
# The data file includes the variables:
# 
# DC 	 death/censoring indicator 
# 	 1 = death from malignant melanoma, 
#          2 = alive 31DEC77, 
#          3 = death from other causes
# 
# DAYS 	 time in days from operation
# 
# LEVEL 	 level of invasion, 0, 1 or 2
# 
# ICI 	 inflammatory cell infiltration (ICI), 0, 1, 2 or 3
# 
# ECEL 	 presence of epithelioid cells, 1=no, 2=yes
# 
# ULC 	 presence of ulceration, 0=no, 1=yes
# 
# THICK 	 tumour thickness (in mm)
# 
# SEX 	 sex, 0=F, 1=M
# 
# AGE 	 age at operation (years)


library(ggplot2)
#Data loading
melanoma <- read.table('Melanoma.csv', sep=";", head=T)

attach(melanoma)
###########
#summary statistics
###########

#Binary values
melanoma$sex
melanoma$ecel
melanoma$ulc

#Ordinal values
melanoma$level
melanoma$ici

#Nominal values
melanoma$dc


#number of men and women
male <- sum(melanoma$sex > 0)
female <-sum(melanoma$sex < 1)

#people old 40- and 40+
young_p <- sum(melanoma$age <= 40)
old_p <- sum(melanoma$age > 40)


#average age, average age of men and women
av_mean <- mean(melanoma$age)

#make levels
melanoma$sex <- as.factor(as.numeric(melanoma$sex))
melanoma$ulc <- as.factor(as.numeric(melanoma$ulc))
melanoma$ecel <- as.factor(as.numeric(melanoma$ecel))
melanoma$level <- as.factor(as.numeric(melanoma$level))
melanoma$ici <- as.factor(as.numeric(melanoma$ici))

levels(melanoma$ecel)
levels(melanoma$ulc)
levels(melanoma$sex)
levels(melanoma$level)
levels(melanoma$ici)

tapply(melanoma$age, melanoma$sex, mean)

#death from melanoma
sum(melanoma$dc == 1)
dmr <- (sum(melanoma$dc == 1) / nrow(melanoma))* 100

#survive
sum(melanoma$dc == 2)
smr <- (sum(melanoma$dc == 2) / nrow(melanoma))* 100

#death from other causes
sum(melanoma$dc == 3)
dor <-  (sum(melanoma$dc == 3) / nrow(melanoma))* 100

#average of tumor thickness patients 40-
mean(melanoma$thick & melanoma$age <= 40)
mean(melanoma$thick & melanoma$age > 40)


#spread of melanoma over the years
age <- cut(melanoma$age, breaks = seq(0, 100, 5), include.lowest = TRUE)
sex <- melanoma$sex


ggplot(melanoma, aes(x=age, fill=sex)) + geom_histogram(position = 'stack', breaks = seq(0, 100, 5)) +
  labs(title= 'Spread of melanoma by age') +
  scale_fill_manual(values=c('blue','red'), labels=c('Female', 'Male'))

par(mfrow=c(2,2))
#all_pacients
qqnorm(melanoma$age,
            ylab = 'Age')
qqline(melanoma$age, col='red')
shapiro.test(melanoma$age)

#male
qqnorm(melanoma$age[melanoma$sex == 1],
       ylab = 'Age of male')
qqline(melanoma$age[melanoma$sex == 1], col='blue')
shapiro.test(melanoma$age[melanoma$sex == 1])

#female
qqnorm(melanoma$age[melanoma$sex == 0],
       ylab = ' Age of female')
qqline(melanoma$age[melanoma$sex == 0], col='green')
shapiro.test(melanoma$age[melanoma$sex == 0])

#thick
qqnorm(melanoma$thick,
       ylab = 'Thickness of tumor')
qqline(melanoma$thick, col='red')
shapiro.test(melanoma$thick)

#thick after transformation
    qqnorm(log10(melanoma$thick),
           ylab = 'Thickness of tumor')
    qqline(log10(melanoma$thick), col = 'blue')
      
par(mfrow=c(1,1))


########
#Single linear regression
########

#H0: Tumor thickness dont depend on age
plot(melanoma$age ~ log10(melanoma$thick),
     main = 'Tumor thickness by age',
     xlab = 'Tumor thickness [log transformation]',
     ylab = 'Age')

abline(h = 40, col = 'red')

model1 <- lm(melanoma$age ~ log10(melanoma$thick))
summary(model1)

cor.test(melanoma$thick, melanoma$age, method= 'spearman', exact = FALSE)


#The graph shows us patients older than 40 years have higher tumor thickness.
#From model1 we can see that thickness is significant value with p = 0.0229.
#On correlation was used Spearman method over Peasron because of thick variable which has
#not normal distribution of data.

#H0:the size of tumor dont depend on length of survival
plot(melanoma$days ~ log10(melanoma$thick),
     main = 'Tumor thickness by days',
     xlab = 'Tumor thickness [log transformation]',
     ylab = 'Days')

model2 <- lm(melanoma$days ~ log10(melanoma$thick))
summary(model2)

  cor.test(melanoma$thick, melanoma$days, method='spearman', exact = FALSE )


#The p-value is less than the significante level alpha = 0.05.
#My conclusion is that tumor thickness is significantly correlated with length of survival
#I have accepted HA.

#H0: There is no statistically significant difference between median of the length of survival
# by men and women
plot(melanoma$days ~ melanoma$sex,
     xlab = 'Sex',
     ylab = 'Days')

#independent 2-group Mann-Whitney test
wilcox.test(melanoma$days~melanoma$sex)

model_day_sex <- lm(melanoma$days ~ melanoma$sex)
summary(model_day_sex)

model_day_ecel <- lm(melanoma$days ~ melanoma$ecel)
summary(model_day_ecel)

model_day_ulc <- lm(melanoma$days ~ melanoma$ulc)
summary(model_day_ulc)

#chi-squared-test 
#H0: Are they independent?
chisq.test(melanoma$ecel, melanoma$ulc)

######
#Multiple linear regression
######

#Aditive model
model3 <- lm(formula =  days ~ age + log10(thick) + sex + ulc + ecel + level + ici, data = melanoma)
summary(model3)


#interaction model 
model4 <- lm(formula =  days ~ age + log10(thick)*level + ulc + ecel + sex + ici , data = melanoma)
summary(model4)

model5 <- lm(formula =  days ~ age + log10(thick)* ecel + level + ulc + sex , data = melanoma)
summary(model5)

model6 <- lm(formula =  days ~ age + log10(thick)*ecel + level + ulc*sex , data = melanoma)
summary(model6)

anova(model3, model4)
vif(model4)

#Model3 will be used

#######
#residual analysis
#######

plot(resid(model3)~age,
     xlab = "Age",
     ylab = "Residuals",
     main = "Independent variables"
)
abline(0,0,col ='red')


plot(resid(model3)~log10(thick),
            xlab = "Tumor thickness [log10 values]",
            ylab = "Residuals",
            main = "Independent variables"
)
abline(0,0,lty=2)

plot(model3)

#residuals vs fitted
plot(model3, which = 1)

#QQ plot
plot(model3, which = 2)

#pakove body
plot(hatvalues(model3)~log10(thick),
     xlab = "Tumor thickness [log10 values]",
     ylab = "Leverages",
)
  
#DFFITS
plot(dffits(model1)~log10(thick),
     xlab = "Tumor thickness [log10 values]",
     ylab = "DFFITS"
)

#DFBETAS
matplot(log10(thick),dfbetas(model3),xlab="Tumor thickness [log10 values]",
        ylab="DFBETAS",type="p")

#Cook's distance
plot(cooks.distance(model3)~log10(thick),
     xlab = "Tumor thickness [log10 values]",
     ylab = "Cook's distance"
)
