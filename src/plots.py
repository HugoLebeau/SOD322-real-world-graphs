import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.colors import Normalize

# %% tme2-1 Average degree density and Edge density

df_amazon = pd.read_csv("../outputs/densest_prefix_com-amazon.csv")
df_lj = pd.read_csv("../outputs/densest_prefix_com-lj.csv")
df_orkut = pd.read_csv("../outputs/densest_prefix_com-orkut.csv")

for df, title in [(df_amazon, "com-Amazon"), (df_lj, "com-LiveJournal"), (df_orkut, "com-Orkut")] :
    fig, ax = plt.subplots(1, 2, figsize=(10, 4))
    fig.suptitle(title+" — Densest core ordering prefix")
    df.plot(x="Size", y="Average degree density", ax=ax[0], legend=None)
    ax[0].grid(ls=':')
    ax[0].set_xscale('log')
    ax[0].set_title("Average degree density")
    df.plot(x="Size", y="Edge density", ax=ax[1], legend=None)
    ax[1].grid(ls=':')
    ax[1].set_xscale('log')
    ax[1].set_title("Edge density")
    plt.show()

# %% tme2-2 Coreness vs. Degree

df = pd.read_csv("../outputs/degree_coreness_scholar.csv")
ID = pd.read_csv("../data/scholar/ID.txt", sep='$', header=None)
ID = ID[0].apply(lambda s: ' '.join(s.split(" ")[1:]))
ID.name = "Name"

df.plot.scatter(x="Degree", y="Coreness", edgecolor=[])
plt.grid(ls=':')
plt.title("Google Scholar")
plt.show()

print(ID.loc[df[df["Coreness"] == 14]["ID"].values])

# %% tme3-1&2 PageRank

df = pd.read_csv("../outputs/page_rank.csv")
num2name = pd.read_csv("../data/alr21--pageNum2Name--enwiki-20071018.txt", sep=None, engine='python', header=None, index_col=0)
num2name.columns = ['ID']
df = df.loc[num2name.index]
df.index = num2name['ID']

print("\nLargest PageRank:")
print(df["0.15"].nlargest(5))
print("\nSmallest PageRank:")
print(df["0.15"].nsmallest(5))
print("\nSmallest positive PageRank:")
print(df[df["0.15"] > 0.]["0.15"].nsmallest(5))

mask = df["0.15"] > 0.
plt.scatter(np.log(df[mask]["0.15"]), np.log(df[mask]["In-degree"]))
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel("log In-degree")
plt.show()

mask = df["0.15"] > 0.
plt.scatter(np.log(df[mask]["0.15"]), np.log(df[mask]["Out-degree"]))
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel("log Out-degree")
plt.show()

mask = (df["0.15"] > 0.) & (df["0.10"] > 0.)
plt.scatter(np.log(df[mask]["0.15"]), np.log(df[mask]["0.10"]))
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.10$")
plt.show()

mask = (df["0.15"] > 0.) & (df["0.20"] > 0.)
plt.scatter(np.log(df[mask]["0.15"]), np.log(df[mask]["0.20"]))
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.20$")
plt.show()

mask = (df["0.15"] > 0.) & (df["0.50"] > 0.)
plt.scatter(np.log(df[mask]["0.15"]), np.log(df[mask]["0.50"]))
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.50$")
plt.show()

mask = (df["0.15"] > 0.) & (df["0.90"] > 0.)
plt.scatter(np.log(df[mask]["0.15"]), np.log(df[mask]["0.90"]))
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.90$")
plt.show()

matcorr = df[["In-degree", "Out-degree", "0.15", "0.10", "0.20", "0.50", "0.90"]].corr()
dic = {"0.15": r"PageRank $\alpha = 0.15$",
       "0.10": r"PageRank $\alpha = 0.10$",
       "0.20": r"PageRank $\alpha = 0.20$",
       "0.50": r"PageRank $\alpha = 0.50$",
       "0.90": r"PageRank $\alpha = 0.90$"}
matcorr.rename(index=dic, columns=dic, inplace=True)
norm = Normalize(-1, 1)
plt.imshow(matcorr, cmap='bwr', norm=norm, interpolation='none')
xticks = range(matcorr.shape[1])
yticks = range(matcorr.shape[0])
plt.xticks(ticks=xticks, labels=matcorr.columns, rotation=90)
plt.yticks(ticks=yticks, labels=matcorr.index)
for i in xticks:
    for j in yticks:
        plt.text(i, j, matcorr.iloc[j, i].round(2), ha='center', va='center', fontsize='large')
plt.title("Correlations")
plt.show()
