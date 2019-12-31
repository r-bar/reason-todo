type item = {
  id: int,
  text: string,
  completed: bool,
};

type state = {items: list(item)};

let initialState = {
  items: [{id: 0, text: "Write some things to do", completed: false}],
};

type action =
  | ToggleItem(int)
  | AddItem(string);

let css = "
/*
#root {
  align-items: center;
  justify-content: center;
  position: absolute;
  top: 0;
  left: 0;
  bottom: 0;
  right: 0;
}
*/

.disabled {
  text-decoration: line-through;
}

.app {
  font-family: sans-serif;
  display: flex;
  flex-direction: column;
  box-sizing: border-box;
  flex-shrink: 0;
  align-items: center;
  justify-content: center;
  position: absolute;

  width: 300px;
  max-height: 600px;
  flex: 1;
  box-shadow: 0 2px 15px #ccc;
  margin: 10px;
  align-items: stretch;
}

.title {
  text-align: center;
  font-size: 20px;
  align-items: center;
  padding: 20px;
}

.items {
  margin: 10px 0;
  text-align: center;
  flex: 1;
  overflow: auto;
}

.footer {
  align-items: flex-start;
  padding: 5px 10px;
}

.item {
  display: flex;
  padding: 10px 20px;
  align-items: center;
  flex-direction: row;
}

.checkbox {
  margin-right: 20px;
}

input[type=\"checkbox\"] {
  margin-right: 10px;
}

input[type=\"text\"] {
  align-self: stretch;
  padding: 3px 5px;
  margin-top: 20px;
}
";

module TodoItem = {
  let lastId = ref(0);
  let newItem = (text): item => {
    lastId := lastId^ + 1;
    {id: lastId^, text, completed: false};
  };

  [@reactComponent]
  let make = (~item, ~onToggle) => {
    let classes = "item" ++ (item.completed ? " disabled" : "");
    <div className=classes>
      <input
        onClick={_evt => onToggle()}
        type_="checkbox"
        checked={item.completed}
        //TODO: make interactive
      />
      {React.string(item.text)}
    </div>;
  };
};

module Input = {
  type state = string;

  [@react.component]
  let make = (~onSubmit) => {
    let (text, setText) =
      React.useReducer((_oldText, newText) => newText, "");
    <input
      value=text
      type_="text"
      placeholder="Write something to do"
      onChange={evt => ReactEvent.Form.target(evt)##value->setText}
      onKeyDown={evt =>
        if (ReactEvent.Keyboard.key(evt) == "Enter") {
          onSubmit(text);
          setText("");
        }
      }
    />;
  };
};

let update = (state, action) => {
  switch (action) {
  | ToggleItem(id) =>
    let items =
      List.map(state.items, item =>
        item.id == id ? {...item, completed: !item.completed} : item
      );
    {items: items};
  | AddItem(text) => {items: [TodoItem.newItem(text), ...state.items]}
  };
};

[@react.component]
let make = (~title) => {
  let ({items}, dispatch) = React.useReducer(update, initialState);

  let itemsEl =
    items
    ->List.map(item =>
        TodoItem.make(~item, ~onToggle=() => dispatch(ToggleItem(item.id)))
      )
    ->ArrayLabels.of_list;
  let numItems = List.length(items);

  <div className="app">
    <style> {React.string(css)} </style>
    <div className="title"> {React.string(title)} </div>
    <Input onSubmit={text => dispatch(AddItem(text))} />
    <div className="items"> {React.array(itemsEl)} </div>
    <div className="footer">
      {React.string(string_of_int(numItems) ++ " items")}
    </div>
  </div>;
};
