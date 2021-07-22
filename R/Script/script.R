#library na regex
#library(stringr)
#load data



data <-load(file = "GSE11543.Rdata") 
if(is.data.frame(data)){
  names(data)
}
#check in the case is not data.frame
data <- as.data.frame(ukol4_data)


## annotation
as.data.frame(annot)

#patients
clinical
clinical$patient

#data axis x
#res$gene_symbol <- rownames(res)
res$gene_symbol <- NULL
new_res <- res[c('HIST1H2BE', 'DNAH17', 'H3F3B', 'SOX9', 'EIF4G3', 
                 'ITGA1', 'TIMM44', 'ZNF43', 'M6PR', 'PGF', 'PTPRB', 
                 'CXCL3', 'JUND', 'HIST1H1C', 'SLC7A1'),]

new_res$gene_symbol <- rownames(new_res)



#function returns chosen row, then can be used str_extract or grepl
row_clinical <- function(p_index)
{
  return(do.call(paste, clinical[c(p_index), ]))
}


#returns type of symbol depends on sex/MSDNA
symbol_type <- function(pa_index)
{
  if(grepl('MSS', row_clinical(pa_index)) & grepl('F', row_clinical(pa_index)))
  {
    return(13)#cross circle
  }
  else if(grepl('MSI', row_clinical(pa_index)) & grepl('F', row_clinical(pa_index)))
  {
    return(2)#empty triangle
  }
  else if(grepl('MSS', row_clinical(pa_index)) & grepl('M', row_clinical(pa_index)))
  {
    return(15)#full square
  }
  else if(grepl('MSI', row_clinical(pa_index)) & grepl('M', row_clinical(pa_index)))
  {
    return(16)#full circle
  }
}

#random pacient
decide <- function(x)
{
  n <- sample(1:51, 1)
  if (x == 1)
  {
    p1 <<- (colnames(new_res) [n])
  }
  else if (x == 2)
  {
    p2 <<- (colnames(new_res) [n])
  }
  else if (x== 3)
  {
    p3 <<- (colnames(new_res) [n])
  }
  else if (x == 4)
  {
    p4 <<- (colnames(new_res) [n])
  }
  else if (x == 5)
  {
    p5 <<- (colnames(new_res) [n])
  }
  else
  {
    p6 <<- (colnames(new_res) [n])
  }
    
  return (new_res[[n]])
}

par(xpd = T, mar = par()$mar + c(0,0,0,8))

graph_data <-plot(c(1:15),  as.numeric(as.character(decide(1))), ylim=c(5,15), ylab = 'Expresion', xlab = '',
xaxt='n', pch = symbol_type(p1), type='o', col='red')
lines(c(1:15), as.numeric(as.character(decide(2))), pch = symbol_type(p2), type='o', col ='black')
lines(c(1:15), as.numeric(as.character(decide(3))), pch = symbol_type(p3), type='o', col ='green')
lines(c(1:15), as.numeric(as.character(decide(4))), pch = symbol_type(p4), type='o', col ='pink')
lines(c(1:15), as.numeric(as.character(decide(5))), pch = symbol_type(p5), type='o', col ='blue')
lines(c(1:15), as.numeric(as.character(decide(6))), pch = symbol_type(p6), type='o', col ='purple')

axis(1, at=c(1:15), labels=c('HIST1H2BE', 
'DNAH17', 'H3F3B', 'SOX9', 'EIF4G3', 'ITGA1', 'TIMM44', 'ZNF43', 'M6PR', 
'PGF', 'PTPRB', 'CXCL3', 'JUND', 'HIST1H1C', 'SLC7A1'), las=3)

legend(x = 16, y = 15.4,  inset=c(3,0),legend=c(p1, p2, p3, p4, p5, p6),
       fill=c(2,'black','green','pink', 4,'purple'), bty = "n", title='Pacient:')
legend(x = 16, y = 7.9, legend=c('Men/MSI', 'Men/MSS', 'Women/MSI', 'Women/MSS'), 
       pch =c(16, 15, 2, 13), bty = "n", title='Group:')

setwd(system("pwd", intern = T) )
dev.copy(png, 'graph_data4.png')
#also can be used png(file='graph_data2.png')
dev.off()







