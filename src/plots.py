import networkx as nx
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.colors import Normalize
from sklearn.metrics import adjusted_rand_score, normalized_mutual_info_score

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

pagerank = pd.read_csv("../outputs/page_rank_enwiki.csv")
page_num2name = pd.read_csv("../data/alr21--pageNum2Name--enwiki-20071018.txt", sep=None, engine='python', header=None, index_col=0)
page_num2name.columns = ["ID"]
page_num2name.index.name = "Page"
pagerank = pagerank.loc[page_num2name.index]
pagerank.index = page_num2name["ID"]

print("\nLargest PageRank:")
print(pagerank["0.15"].nlargest(5))
print("\nSmallest PageRank:")
print(pagerank["0.15"].nsmallest(5))

plt.scatter(np.log(pagerank["0.15"]), np.log(pagerank["In-degree"]), s=3)
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel("log In-degree")
plt.show()

plt.scatter(np.log(pagerank["0.15"]), np.log(pagerank["Out-degree"]), s=3)
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel("log Out-degree")
plt.show()

plt.scatter(np.log(pagerank["0.15"]), np.log(pagerank["0.10"]), s=3)
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.10$")
plt.show()

plt.scatter(np.log(pagerank["0.15"]), np.log(pagerank["0.20"]), s=3)
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.20$")
plt.show()

plt.scatter(np.log(pagerank["0.15"]), np.log(pagerank["0.50"]), s=3)
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.50$")
plt.show()

plt.scatter(np.log(pagerank["0.15"]), np.log(pagerank["0.90"]), s=3)
plt.grid(ls=':')
plt.xlabel(r"log PageRank $\alpha = 0.15$")
plt.ylabel(r"log PageRank $\alpha = 0.90$")
plt.show()

matcorr = pagerank[["In-degree", "Out-degree", "0.15", "0.10", "0.20", "0.50", "0.90"]].corr()
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

# %% tme3-3 Rooted PageRank

rootedpagerank = pd.read_csv("../outputs/rooted_page_rank_Magnus_Carlsen.csv")
rootedpagerank = rootedpagerank.loc[page_num2name.index]
rootedpagerank.sort_values(by="RootedPageRank", ascending=False, inplace=True)
rootedpagerank["Name"] = page_num2name.loc[rootedpagerank["Node"]]

print(rootedpagerank[:20])

categ_num2name = pd.read_csv("../data/alr21--categNum2Name--enwiki-20071018.txt", sep=None, engine='python', header=None, index_col=0)
categ_num2name.columns = ["Category"]
categ_num2name.index.name = "ID"

categ = pd.read_csv("../data/alr21--pageCategList--enwiki--20071018.txt", sep=None, engine='python', header=None, index_col=0)
categ.columns = ["Categories"]
categ.index.name = 'Page'
categ["Categories"] = categ["Categories"].apply(lambda x: x.split(' ') if x else [])
categ["Categories"] = categ["Categories"].apply(lambda x: [int(c) for c in x])

id_chess = set(categ_num2name[categ_num2name["Category"].apply(lambda x : "chess" in x.lower())].index)
chess_pages = categ["Categories"].apply(lambda x: len(id_chess.intersection(x)) > 0)

mask = rootedpagerank["RootedPageRank"] > 1e-7

fig, ax = plt.subplots(2, 1, figsize=(6, 6))
ax[0].plot(rootedpagerank[mask]["RootedPageRank"].values)
ax[0].grid(ls=':')
ax[0].set_xscale('log')
ax[0].set_yscale('log')
ax[0].set_ylabel("Proximity to Magnus Carlsen")
ax[1].plot(chess_pages.loc[rootedpagerank[mask]["Node"]].values.cumsum())
ax[1].grid(ls=':')
ax[1].set_xscale('log')
ax[1].set_xlabel("Rank of the node")
ax[1].set_ylabel("Number of nodes related to chess")
plt.show()

chess_boxing = pd.read_csv("../outputs/rooted_page_rank_Magnus_Carlsen_Mike_Tyson.csv")
chess_boxing = chess_boxing.loc[page_num2name.index]
chess_boxing.sort_values(by="RootedPageRank", ascending=False, inplace=True)
chess_boxing["Name"] = page_num2name.loc[chess_boxing["Node"]]

print(chess_boxing[:20])

# %% tme4-1

G = nx.read_edgelist("../outputs/gen_graph_0.5_0.1.csv")
nx.draw(G, arrows=False, node_size=50)
plt.title(r"$p = 0.5$   $q = 0.1$")
plt.show()

G = nx.read_edgelist("../outputs/gen_graph_0.5_0.05.csv")
nx.draw(G, arrows=False, node_size=50)
plt.title(r"$p = 0.5$   $q = 0.05$")
plt.show()

G = nx.read_edgelist("../outputs/gen_graph_0.5_0.01.csv")
nx.draw(G, arrows=False, node_size=50)
plt.title(r"$p = 0.5$   $q = 0.01$")
plt.show()

G = nx.read_edgelist("../outputs/gen_graph_0.9_0.01.csv")
nx.draw(G, arrows=False, node_size=50)
plt.title(r"$p = 0.9$   $q = 0.01$")
plt.show()

# %% tme4-2

labels = pd.read_csv("../outputs/labels_0.5_0.1.csv", index_col=0)
G = nx.read_edgelist("../outputs/gen_graph_0.5_0.1.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels["Label"][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.5$   $q = 0.1$   Label propagation")
plt.show()

labels = pd.read_csv("../outputs/labels_0.5_0.05.csv", index_col=0)
G = nx.read_edgelist("../outputs/gen_graph_0.5_0.05.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels["Label"][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.5$   $q = 0.05$   Label propagation")
plt.show()

labels = pd.read_csv("../outputs/labels_0.5_0.01.csv", index_col=0)
G = nx.read_edgelist("../outputs/gen_graph_0.5_0.01.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels["Label"][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.5$   $q = 0.01$   Label propagation")
plt.show()

labels = pd.read_csv("../outputs/labels_0.9_0.01.csv", index_col=0)
G = nx.read_edgelist("../outputs/gen_graph_0.9_0.01.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels["Label"][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.9$   $q = 0.01$   Label propagation")
plt.show()

# %% tme4-3 Plots

labels = pd.read_csv("../outputs/louvain_0.5_0.1.csv", index_col=0, sep=' ', header=None)
G = nx.read_edgelist("../outputs/gen_graph_0.5_0.1.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels[1][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.5$   $q = 0.1$   Louvain algorithm")
plt.show()

labels = pd.read_csv("../outputs/louvain_0.5_0.05.csv", index_col=0, sep=' ', header=None)
G = nx.read_edgelist("../outputs/gen_graph_0.5_0.05.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels[1][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.5$   $q = 0.05$   Louvain algorithm")
plt.show()

labels = pd.read_csv("../outputs/louvain_0.5_0.01.csv", index_col=0, sep=' ', header=None)
G = nx.read_edgelist("../outputs/gen_graph_0.5_0.01.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels[1][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.5$   $q = 0.01$   Louvain algorithm")
plt.show()

labels = pd.read_csv("../outputs/louvain_0.9_0.01.csv", index_col=0, sep=' ', header=None)
G = nx.read_edgelist("../outputs/gen_graph_0.9_0.01.csv")
nx.draw(G, arrows=False, node_size=50, node_color=labels[1][np.array(G.nodes, dtype=np.int)])
plt.title(r"$p = 0.9$   $q = 0.01$   Louvain algorithm")
plt.show()

# %% tme4-3 Compute ARI and NMI

res_labelprop = pd.DataFrame(index=["0.5_0.1", "0.5_0.05", "0.5_0.01", "0.9_0.01", "500", "1000", "10000", "50000"], columns=["ARI", "NMI"])
res_louvain = pd.DataFrame(index=["0.5_0.1", "0.5_0.05", "0.5_0.01", "0.9_0.01", "500", "1000", "10000", "50000"], columns=["ARI", "NMI"])

for idx in ["0.5_0.1", "0.5_0.05", "0.5_0.01", "0.9_0.01"]:
    labels = np.arange(400)%4
    labelprop = pd.read_csv("../outputs/labels_"+idx+".csv", index_col=0)["Label"].values
    louvain = pd.read_csv("../outputs/louvain_"+idx+".csv", index_col=0, sep=' ', header=None)[1].values
    res_labelprop.loc[idx, "ARI"] = adjusted_rand_score(labels, labelprop)
    res_labelprop.loc[idx, "NMI"] = normalized_mutual_info_score(labels, labelprop)
    res_louvain.loc[idx, "ARI"] = adjusted_rand_score(labels, louvain)
    res_louvain.loc[idx, "NMI"] = normalized_mutual_info_score(labels, louvain)

for idx in ["500", "1000", "10000", "50000"]:
    labels = pd.read_csv("../outputs/community_"+idx+".dat", sep='\t', header=None)[1].values
    labelprop = pd.read_csv("../outputs/labels_"+idx+".csv", index_col=0)["Label"].values[1:]
    louvain = pd.read_csv("../outputs/louvain_"+idx+".csv", index_col=0, sep=' ', header=None)[1].values[1:]
    res_labelprop.loc[idx, "ARI"] = adjusted_rand_score(labels, labelprop)
    res_labelprop.loc[idx, "NMI"] = normalized_mutual_info_score(labels, labelprop)
    res_louvain.loc[idx, "ARI"] = adjusted_rand_score(labels, louvain)
    res_louvain.loc[idx, "NMI"] = normalized_mutual_info_score(labels, louvain)

print(res_labelprop)
print(res_louvain)
