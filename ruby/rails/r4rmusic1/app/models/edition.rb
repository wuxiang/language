class Edition < ActiveRecord::Base
  # attr_accessible :title, :body
  belongs_to :work
end
