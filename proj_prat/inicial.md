  Para facilitar o desenvolvimento do projeto prático, serão anotadas aqui algumas ideias
  e como eles podem ser implementadas em função de objetos.
  
  ## 1 wordle

        Um jogo simples, aonde o jogador deve adivinhar uma pequena palavra a partir de dicas como
      se uma letra entrada é presente na palavra e se esta se encontra no exato local em que foi
      digitada ou não.
      
        Para implementá-lo, é possível criar containers gráficos para cada letra e utilizar um par
      gerador:dicionário para selecionar uma palavra curada aleatória.
      
  ## 2 Simulação Monte-Carlo

        Uma simulação probabilística simples com o intuito de estimar numericamente a chance de uma
      determinada combinação de eventos com probabilidades e interações conhecidas.
      
        É possível implementá-la tratando cada evento como uma instanciação que contém uma probabilidade
      própria isolada e um critério de interação com outros eventos. Isto pode ser relativamente
      complexo.
      
  ## 3 Todo list / notes

        Uma lista que pode ser modificada pelo usuário com checkmarks e notas.
        
        A implementação pode ser feita tratando cada nota como um objeto contendo um valor denominando
      se esta é uma checklist ou uma nota comum, além do texto contido nela e se um ítem foi da checklist
      foi completado.
      
        Os elementos e seus conteúdos podem ser salvos em um arquivo .jsn
