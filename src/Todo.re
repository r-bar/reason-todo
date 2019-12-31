/*
 *module Styles = {
 *  open Css;
 *
 *  let app = style([
 *    width(px(200)),
 *    maxHeight(px(600)),
 *    flex(1),
 *    boxShadow(0, px(2), px(15), hex("#cca"))
 *  ])
 *}
 */


type item = {
  title: string,
  completed: bool,
};

type state = {
  items: list(item),
};

type action =
  | AddItem;

let style = {
  <style>(
    React.string("
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
    "))
  </style>

};

let newItem = (): item => {title: "", completed: false};

module TodoItem = {
  [@reactComponent]
  let make = (~item) => {
    <div className="item">
      <input
        type_="checkbox"
        checked=(item.completed)
        //TODO: make interactive
      />
      (React.string(item.title))
    </div>
  };
};

[@react.component]
let make = (~title) => {
  let initialState = {
    items: [
      {title: "Write some things to do", completed: false}
    ]
  };

  let ({items}, dispatch) = React.useReducer((state, action) => {
    // we dont have any transitions yet
    switch action {
      | AddItem => {items: [newItem(), ...state.items]};
    }
  }, initialState);

  let itemsEl = List.map(items, (item) => TodoItem.make(~item=item))
    -> ArrayLabels.of_list;
  let numItems = List.length(items);
  <div className="app">
    style
    <div className="title">(React.string(title))</div>
    <button onClick=((_evt) => dispatch(AddItem))>
      (React.string("Add something"))
    </button>
    <div className="items">
      (React.array(itemsEl))
    </div>
    <div className="footer">
      (React.string(string_of_int(numItems) ++ " items"))
    </div>
  </div>
};
