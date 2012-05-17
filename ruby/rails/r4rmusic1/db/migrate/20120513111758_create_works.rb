class CreateWorks < ActiveRecord::Migration
  def change
    create_table :works do |t|

      t.timestamps
    end
  end
end
