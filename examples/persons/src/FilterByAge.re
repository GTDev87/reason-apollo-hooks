module PersonsOlderThanQuery = [%graphql
  {|
  query getPersonsOlderThan($age: Int!) {
    allPersons(filter: { age_gte: $age } ) {
      id
    }
  }
|}
];

[@react.component]
let make = (~age) => {
  let (simple, _full) =
    ApolloHooks.useQuery(~query=PersonsOlderThanQuery.make(~age, ()), ());

  <div>
    {switch (simple) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       <h3>
         {"There are "
          ++ (data##allPersons->Belt.Array.length |> string_of_int)
          ++ " people older than "
          ++ string_of_int(age)
          |> React.string}
       </h3>
     | NoData
     | Error(_) => <p> {React.string("Error")} </p>
     }}
  </div>;
};