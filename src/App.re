open ReactUtils;

module AppRouter = Router.Create(Router.Config);

[@react.component]
let make = () => {
  open Router;
  /*open Router.Config;*/
  <div>
    <nav>
      <Link to_=Config.Home> "Home"->s </Link>
      <Link to_=Config.About> "About"->s </Link>
      <Link to_=Config.Todo> "Todo"->s </Link>
    </nav>
    <AppRouter>
      {currentRoute =>
         Router.Config.(
           switch (currentRoute) {
           | Home =>
            { <div>
                <h1> "Home"->s </h1>
                <p> "Hello it is ryan"->s </p>
              </div>
            }
           | About => <h1> "About"->s </h1>
           | NotFound => <div> "Page not found, sorry"->s </div>
           | Todo => <Todo title="hello world" />
           }
         )}
    </AppRouter>
  </div>;
};
