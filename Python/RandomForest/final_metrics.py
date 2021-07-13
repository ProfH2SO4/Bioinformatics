import pandas as pd
import pickle
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import confusion_matrix, accuracy_score, recall_score, f1_score, precision_score
from sklearn.svm import SVC
from sklearn.metrics import plot_confusion_matrix
from matplotlib import pyplot as plt
from sklearn.metrics import plot_precision_recall_curve
from sklearn.metrics import roc_curve, auc
from sklearn.ensemble import RandomForestClassifier


# Input: takes .csv file created by final.py
# Output: F1 score, recall, precision, accuracy
# Logistic and SVM model was used
#

def con_mat():
    with open("data.csv", 'r') as f:
        data = pd.read_csv(f, delimiter=',')
        data_df = pd.DataFrame(data, index=None)
        # print(data_df)
        y = data_df.iloc[:, 0]
        X = data_df.iloc[:, 1:]
        X_train, X_test, y_train, y_test = train_test_split(
            X, y, test_size=0.2, random_state=42)
        # Logistic model
        log_reg = LogisticRegression()
        log_reg.fit(X_train, y_train)
        yy_pred = log_reg.predict(X_test)
        # SVM model
        model_svm = SVC()
        model_svm.fit(X_train, y_train)
        y_pred_svm = model_svm.predict(X_test)
        # RandomClassifierModel
        model_rclas = RandomForestClassifier(n_estimators=40)
        model_rclas.fit(X_train, y_train)
        y_pred_rclas = model_rclas.predict(X_test)

        # cm_rclas = confusion_matrix(y_test, y_pred_rclas)
        # print(cm_rclas)
        # Log model output
        cm_log = confusion_matrix(y_test, yy_pred)
        acc_log = accuracy_score(y_test, yy_pred)
        rs_log = recall_score(y_test, yy_pred)
        pre_log = precision_score(y_test, yy_pred)
        f1_s_log = f1_score(y_test, yy_pred)

        # Support vector output
        cm_svm = confusion_matrix(y_test, y_pred_svm)
        acc_svm = accuracy_score(y_test, y_pred_svm)
        rs_svm = recall_score(y_test, y_pred_svm)
        pre_svm = precision_score(y_test, y_pred_svm)
        f1_s_svm = f1_score(y_test, y_pred_svm)

        # RandomForest output
        cm_forest = confusion_matrix(y_test, y_pred_rclas)
        acc_forest = accuracy_score(y_test, y_pred_rclas)
        rs_forest = recall_score(y_test, y_pred_rclas)
        pre_forest = precision_score(y_test, y_pred_rclas)
        f1_s_forest = f1_score(y_test, y_pred_rclas)

        # save SVM model
        file_svm = 'svm_model.sav'
        pickle.dump(model_svm, open(file_svm, 'wb'))
        # save RandomForest model
        file_forest = 'forest_model.sav'
        pickle.dump(model_rclas, open(file_forest, 'wb'))

        # ROC curve
        logistic_fpr, logistic_tpr, threshold = roc_curve(y_test, yy_pred)
        auc_logistic = auc(logistic_fpr, logistic_tpr)

        svm_fpr, svm_tpr, threshold = roc_curve(y_test, y_pred_svm)
        auc_svm = auc(svm_fpr, svm_tpr)

        rclas_fpr, rclas_tpr, threshold = roc_curve(y_test, y_pred_rclas)
        auc_rclas = auc(rclas_fpr, rclas_tpr)

        plt.figure(figsize=(5, 5), dpi=100)
        plt.plot(svm_fpr, svm_tpr, linestyle='-', label='SVM (auc = %0.3f)' % auc_svm)
        plt.plot(logistic_fpr, logistic_tpr, marker='.', label='Logistic (auc = %0.3f)' % auc_logistic)
        plt.plot(rclas_fpr, rclas_tpr, marker='o', label='RandomForest (auc = %0.3f)' % auc_rclas)
        plt.plot([0, 1], [0, 1], color='navy', linestyle='--')
        plt.xlabel('False Positive Rate')
        plt.ylabel('True Positive Rate')
        plt.legend()
        plt.show()
        # plot confusion matrix
        plot_confusion_matrix(log_reg, X_test, y_test)
        plt.show()
        # plot prec by recall log_reg
        plot_precision_recall_curve(log_reg, X_test, y_test)
        plt.show()
        # plot prec by recall SVM
        plot_precision_recall_curve(model_svm, X_test, y_test)
        plt.show()
        # plot prec by recall RandomForest
        plot_precision_recall_curve(model_rclas, X_test, y_test)
        plt.show()

        print('-----------Log regresion model-------------')
        print('Confusion matrix')
        print(cm_log)
        print('Accuracy score is ', acc_log)
        print('Recall score is ', rs_log)
        print('Precision score is ', pre_log)
        print('F1_score is ', f1_s_log)
        print('-' * 40)
        print('------------SVM model---------------------')
        print('Confusion matrix')
        print(cm_svm)
        print('Accuracy score is ', acc_svm)
        print('Recall score is ', rs_svm)
        print('Precision score is ', pre_svm)
        print('F1_score is ', f1_s_svm)
        print('-' * 40)
        print('------------RandomForest model---------------------')
        print('Confusion matrix')
        print(cm_forest)
        print('Accuracy score is ', acc_forest)
        print('Recall score is ', rs_forest)
        print('Precision score is ', pre_forest)
        print('F1_score is ', f1_s_forest)


con_mat()
