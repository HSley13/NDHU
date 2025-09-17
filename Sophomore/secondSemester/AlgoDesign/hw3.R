library(ggplot2)

df <- base::data.frame(
  Algorithm = c("DFS", "BFS", "Best-First"),
  MaxProfit = c(15, 15, 15),
  NodesVisited = c(27, 63, 12)
)

p <- ggplot2::ggplot(df, ggplot2::aes(x = Algorithm, y = NodesVisited, fill = Algorithm)) +
  ggplot2::geom_bar(stat = "identity", width = 0.6) +
  ggplot2::labs(
    title = "Nodes Visited by Algorithm (Single Case)",
    y = "Number of Nodes Visited",
    x = "Search Algorithm"
  ) +
  ggplot2::theme_bw() +
  ggplot2::geom_text(ggplot2::aes(label = NodesVisited), vjust = -0.5) +
  ggplot2::theme(legend.position = "none")

ggplot2::ggsave("hw3.png", p, width = 6, height = 5)
